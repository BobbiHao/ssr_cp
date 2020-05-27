#include "X11Input.h"

X11Input::X11Input(unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool record_cursor, bool follow_cursor, bool follow_fullscreen)
{
   m_x = x;
   m_y = y;
   m_width = width;
   m_height = height;
   m_record_cursor = record_cursor;
   m_follow_cursor = follow_cursor;
   m_follow_fullscreen = follow_fullscreen;

   m_x11_display = NULL;
   m_x11_image = NULL;
   m_x11_shm_info.shmseg = 0;
   m_x11_shm_info.shmid = -1;
   m_x11_shm_info.shmaddr = (char*)-1;
   m_x11_shm_info.readOnly = false;
   m_x11_shm_server_attached = false;

   m_screen_bbox = Rect(m_x, m_y, m_x + m_width, m_y + height);
   {
       SharedLock lock(&m_shared_data);
       lock->m_current_width = m_width;
       lock->m_current_height = m_height;
   }

   if (m_width == 0 || m_height == 0) {
       Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Width or height is zero!"));
       throw X11Exception();
   }
   if (m_width > SSR_MAX_IMAGE_SIZE || m_height > SSR_MAX_IMAGE_SIZE) {
       Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Width or height is too large, the maximum width and height is %1!").arg(SSR_MAX_IMAGE_SIZE));
       throw X11Exception();
   }

   try {
       Init();
   } catch(...) {
       Free();
       throw;
   }

}

void X11Input::GetCurrentSize(unsigned int *width, unsigned int *height)
{
    SharedLock lock(&m_shared_data);
    *width = lock->m_current_width;
    *height = lock->m_current_height;
}

void X11Input::Init()
{
    // do the X11 stuff
    // we need a separate display because the existing one would interfere with what Qt is doing in some cases
    m_x11_display = XOpenDisplay(NULL); //QX11Info::display();
    if(m_x11_display == NULL) {
        Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Can't open X display!", "Don't translate 'display'"));
        throw X11Exception();
    }
    m_x11_screen = DefaultScreen(m_x11_display); //QX11Info::appScreen();
    m_x11_root = RootWindow(m_x11_display, m_x11_screen); //QX11Info::appRootWindow(m_x11_screen);
    m_x11_visual = DefaultVisual(m_x11_visual, m_x11_screen);
    m_x11_depth = DefaultDepth(m_x11_display, m_x11_screen);
    m_x11_use_shm = XShmQueryExtension(m_x11_display);
    if(m_x11_use_shm) {
        Logger::LogInfo("[X11Input::Init] " + Logger::tr("Using X11 shared memory."));
    } else {
        Logger::LogInfo("[X11Input::Init] " + Logger::tr("Not using X11 shared memory."));
    }

    // showing the cursor requires XFixes (which should be supported on any modern X server, but let's check it anyway)
    if(m_record_cursor) {
        int event, error;
        if(!XFixesQueryExtension(m_x11_display, &event, &error)) {
            Logger::LogWarning("[X11Input::Init] " + Logger::tr("Warning: XFixes is not supported by X server, the cursor has been hidden.", "Don't translate 'XFixes'"));
            m_record_cursor = false;
        }
    }

    // get screen configuration information, so we can replace the unused areas with black rectangles (rather than showing random uninitialized memory)
    // this is also used by the mouse following code to make sure that the rectangle stays on the screen
    UpdateScreenConfiguration();

    // initialize frame counter
    m_frame_counter = 0;
    m_fps_last_timestamp = hrt_time_micro();
    m_fps_last_counter = 0;
    m_fps_current = 0.0;

    // start input thread
    m_should_stop = false;
    m_error_occurred = false;
    m_thread = std::thread(&X11Input::InputThread, this);

}

void X11Input::Free()
{
    FreeImage();
    if(m_x11_display != NULL) {
        XCloseDisplay(m_x11_display);
        m_x11_display = NULL;
    }

}

void X11Input::AllocateImage(unsigned int width, unsigned int height)
{
    assert(m_x11_use_shm);
    if(m_x11_shm_server_attached && m_x11_image->width == (int) width && m_x11_image->height == (int) height) {
        return; // reuse existing image
    }
    FreeImage();
    m_x11_image = XShmCreateImage(m_x11_display, m_x11_visual, m_x11_depth, ZPixmap, NULL, &m_x11_shm_info, width, height);
    if(m_x11_image == NULL) {
        Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Can't create shared image!"));
        throw X11Exception();
    }
    m_x11_shm_info.shmid = shmget(IPC_PRIVATE, m_x11_image->bytes_per_line * m_x11_image->height, IPC_CREAT | 0700);
    if(m_x11_shm_info.shmid == -1) {
        Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Can't get shared memory!"));
        throw X11Exception();
    }
    m_x11_shm_info.shmaddr = (char*) shmat(m_x11_shm_info.shmid, NULL, SHM_RND);
    if(m_x11_shm_info.shmaddr == (char*) -1) {
        Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Can't attach to shared memory!"));
        throw X11Exception();
    }
    m_x11_image->data = m_x11_shm_info.shmaddr;
    if(!XShmAttach(m_x11_display, &m_x11_shm_info)) {
        Logger::LogError("[X11Input::Init] " + Logger::tr("Error: Can't attach server to shared memory!"));
        throw X11Exception();
    }
    m_x11_shm_server_attached = true;
}

void X11Input::FreeImage()
{
    if(m_x11_shm_server_attached) {
        XShmDetach(m_x11_display, &m_x11_shm_info);
        m_x11_shm_server_attached = false;
    }
    if(m_x11_shm_info.shmaddr != (char*) -1) {
        shmdt(m_x11_shm_info.shmaddr);
        m_x11_shm_info.shmaddr = (char*) -1;
    }
    if(m_x11_shm_info.shmid != -1) {
        shmctl(m_x11_shm_info.shmid, IPC_RMID, NULL);
        m_x11_shm_info.shmid = -1;
    }
    if(m_x11_image != NULL) {
        XDestroyImage(m_x11_image);
        m_x11_image = NULL;
    }
}

void X11Input::UpdateScreenConfiguration()
{
    // get screen rectangles
    m_screen_rects.clear();
    int event_base, error_base;
    if(XineramaQueryExtension(m_x11_display, &event_base, &error_base)) {
        int num_screens;
        XineramaScreenInfo *screens = XineramaQueryScreens(m_x11_display, &num_screens);
        try {
            for(int i = 0; i < num_screens; ++i) {
                m_screen_rects.emplace_back(screens[i].x_org, screens[i].y_org, screens[i].x_org + screens[i].width, screens[i].y_org + screens[i].height);
            }
        } catch(...) {
            XFree(screens);
            throw;
        }
        XFree(screens);
    } else {
        Logger::LogWarning("[X11Input::Init] " + Logger::tr("Warning: Xinerama is not supported by X server, multi-monitor support may not work properly.", "Don't translate 'Xinerama'"));
        return;
    }

    // make sure that we have at least one monitor
    if(m_screen_rects.size() == 0) {
        Logger::LogWarning("[X11Input::Init] " + Logger::tr("Warning: No monitors detected, multi-monitor support may not work properly."));
        return;
    }

    // calculate bounding box
    m_screen_bbox = m_screen_rects[0];
    for(size_t i = 1; i < m_screen_rects.size(); ++i) {
        Rect &rect = m_screen_rects[i];
        if(rect.m_x1 < m_screen_bbox.m_x1)
            m_screen_bbox.m_x1 = rect.m_x1;
        if(rect.m_y1 < m_screen_bbox.m_y1)
            m_screen_bbox.m_y1 = rect.m_y1;
        if(rect.m_x2 > m_screen_bbox.m_x2)
            m_screen_bbox.m_x2 = rect.m_x2;
        if(rect.m_y2 > m_screen_bbox.m_y2)
            m_screen_bbox.m_y2 = rect.m_y2;
    }
    if(m_screen_bbox.m_x1 >= m_screen_bbox.m_x2 || m_screen_bbox.m_y1 >= m_screen_bbox.m_y2 ||
       m_screen_bbox.m_x2 - m_screen_bbox.m_x1 > SSR_MAX_IMAGE_SIZE || m_screen_bbox.m_y2 - m_screen_bbox.m_y1 > SSR_MAX_IMAGE_SIZE) {
        Logger::LogError("[X11Input::UpdateScreenConfiguration] " + Logger::tr("Error: Invalid screen bounding box!") + "\n"
                           "    x1 = " + QString::number(m_screen_bbox.m_x1) + ", y1 = " + QString::number(m_screen_bbox.m_y1)
                           + ", x2 = " + QString::number(m_screen_bbox.m_x2) + ", y2 = " + QString::number(m_screen_bbox.m_y2));
        throw X11Exception();
    }

    /*qDebug() << "m_screen_rects:";
    for(Rect &rect : m_screen_rects) {
        qDebug() << "    rect" << rect.m_x1 << rect.m_y1 << rect.m_x2 << rect.m_y2;
    }
    qDebug() << "m_screen_bbox:";
    qDebug() << "    rect" << m_screen_bbox.m_x1 << m_screen_bbox.m_y1 << m_screen_bbox.m_x2 << m_screen_bbox.m_y2;*/

    // calculate dead space
    m_screen_dead_space = {m_screen_bbox};
    for(size_t i = 0; i < m_screen_rects.size(); ++i) {
        /*qDebug() << "PARTIAL m_screen_dead_space:";
        for(Rect &rect : m_screen_dead_space) {
            qDebug() << "    rect" << rect.m_x1 << rect.m_y1 << rect.m_x2 << rect.m_y2;
        }*/
        Rect &subtract = m_screen_rects[i];
        std::vector<Rect> result;
        for(Rect &rect : m_screen_dead_space) {
            if(rect.m_x1 < subtract.m_x2 && rect.m_y1 < subtract.m_y2 && subtract.m_x1 < rect.m_x2 && subtract.m_y1 < rect.m_y2) {
                unsigned int mid_y1 = std::max(rect.m_y1, subtract.m_y1);
                unsigned int mid_y2 = std::min(rect.m_y2, subtract.m_y2);
                if(rect.m_y1 < subtract.m_y1)
                    result.emplace_back(rect.m_x1, rect.m_y1, rect.m_x2, subtract.m_y1);
                if(rect.m_x1 < subtract.m_x1)
                    result.emplace_back(rect.m_x1, mid_y1, subtract.m_x1, mid_y2);
                if(subtract.m_x2 < rect.m_x2)
                    result.emplace_back(subtract.m_x2, mid_y1, rect.m_x2, mid_y2);
                if(subtract.m_y2 < rect.m_y2)
                    result.emplace_back(rect.m_x1, subtract.m_y2, rect.m_x2, rect.m_y2);
            } else {
                result.emplace_back(rect);
            }
        }
        m_screen_dead_space = std::move(result);
    }

    /*qDebug() << "m_screen_dead_space:";
    for(Rect &rect : m_screen_dead_space) {
        qDebug() << "    rect" << rect.m_x1 << rect.m_y1 << rect.m_x2 << rect.m_y2;
    }*/
}

void X11Input::InputThread()
{
    try {
        Logger::LogInfo("[X11Input::InputThread] " + Logger::tr("Input thread started."));

        unsigned int grab_x = m_x, grab_y = m_y, grab_width = m_width, grab_height = m_height;
        bool has_initial_cursor = false;
        int64_t last_timestamp = hrt_time_micro();

        while (!m_should_stop) {

            //sleep
            int64_t next_timestamp = CalculateNextVideoTimestamp();
            int64_t timestamp = hrt_time_micro();
            if (next_timestamp == SINK_TIMESTAMP_NONE) {
                usleep(20000);
                continue;
            } else if (next_timestamp != SINK_TIMESTAMP_ASAP) {
                int64_t wait = next_timestamp - timestamp;
                if (wait > 21000) {
                    // the thread can't sleep for too long because it still has to check the m_should_stop flag periodically
                    usleep(20000);
                    continue;
                } else if (wait > 0) {
                    usleep(wait);
                    timestamp = hrt_time_micro();
                }
            }

            // follow the cursor
            if (m_follow_cursor) {
                int mouse_x, mouse_y, dummy;
                Window dummy_win;
                unsigned int dummy_mask;
                if(XQueryPointer(m_x11_display, m_x11_root, &dummy_win, &dummy_win, &dummy, &dummy, &mouse_x, &mouse_y, &dummy_mask)) {
                    if(m_follow_fullscreen) {
                        for(Rect &rect : m_screen_rects) {
                            if(mouse_x >= (int) rect.m_x1 && mouse_y >= (int) rect.m_y1 && mouse_x < (int) rect.m_x2 && mouse_y < (int) rect.m_y2) {
                                grab_x = rect.m_x1;
                                grab_y = rect.m_y1;
                                grab_width = rect.m_x2 - rect.m_x1;
                                grab_height = rect.m_y2 - rect.m_y1;
                                break;
                            }
                        }
                    } else {
                        int grab_x_target = (mouse_x - (int) grab_width / 2) >> 1;
                        int grab_y_target = (mouse_y - (int) grab_height / 2) >> 1;
                        int frac = (has_initial_cursor)? lrint(1024.0 * exp(-1e-5 * (double) (timestamp - last_timestamp))) : 0;
                        grab_x_target = (grab_x_target + ((int) (grab_x >> 1) - grab_x_target) * frac / 1024) << 1;
                        grab_y_target = (grab_y_target + ((int) (grab_y >> 1) - grab_y_target) * frac / 1024) << 1;
                        grab_x = clamp(grab_x_target, (int) m_screen_bbox.m_x1, (int) m_screen_bbox.m_x2 - (int) grab_width);
                        grab_y = clamp(grab_y_target, (int) m_screen_bbox.m_y1, (int) m_screen_bbox.m_y2 - (int) grab_height);
                    }
                }
                has_initial_cursor = true;
            }

            // save current size
            {
                SharedLock lock(&m_shared_data);
                lock->m_current_width = grab_width;
                lock->m_current_height = grab_height;
            }

            //get the image
            if(m_x11_use_shm) {
                AllocateImage(grab_width, grab_height);
                if(!XShmGetImage(m_x11_display, m_x11_root, m_x11_image, grab_x, grab_y, AllPlanes)) {
                    Logger::LogError("[X11Input::InputThread] " + Logger::tr("Error: Can't get image (using shared memory)!\n"
                                     "    Usually this means the recording area is not completely inside the screen. Or did you change the screen resolution?"));
                    throw X11Exception();
                }
            } else {
                if(m_x11_image != NULL) {
                    XDestroyImage(m_x11_image);
                    m_x11_image = NULL;
                }
                m_x11_image = XGetImage(m_x11_display, m_x11_root, grab_x, grab_y, grab_width, grab_height, AllPlanes, ZPixmap);
                if(m_x11_image == NULL) {
                    Logger::LogError("[X11Input::InputThread] " + Logger::tr("Error: Can't get image (not using shared memory)!\n"
                                     "    Usually this means the recording area is not completely inside the screen. Or did you change the screen resolution?"));
                    throw X11Exception();
                }
            }

        }

    } catch(const std::exception& e) {
        m_error_occurred = true;
        Logger::LogError("[X11Input::InputThread] " + Logger::tr("Exception '%1' in input thread.").arg(e.what()));
    } catch(...) {
        m_error_occurred = true;
        Logger::LogError("[X11Input::InputThread] " + Logger::tr("Unknown exception in input thread."));
    }
}
