#include "ssrtools.h"
#include "ui_ssrtools.h"
#include <QDebug>

#include <QFile>


#include "utils.h"
#include "CommandLineOptions.h"
#include "EnumStrings.h"
#include "X11Input.h"


ENUMSTRINGS(ssr::enum_video_area) = {
    {ssr::enum_video_area::VIDEO_AREA_SCREEN, "screen"},
    {ssr::enum_video_area::VIDEO_AREA_FIXED, "fixed"},
    {ssr::enum_video_area::VIDEO_AREA_CURSOR, "cursor"},
#if SSR_USE_OPENGL_RECORDING
    {PageInput::VIDEO_AREA_GLINJECT, "glinject"},
#endif
};
ENUMSTRINGS(ssr::enum_container) = {
    {ssr::enum_container::CONTAINER_MKV, "mkv"},
    {ssr::enum_container::CONTAINER_MP4, "mp4"},
    {ssr::enum_container::CONTAINER_WEBM, "webm"},
    {ssr::enum_container::CONTAINER_OGG, "ogg"},
    {ssr::enum_container::CONTAINER_OTHER, "other"},
};
ENUMSTRINGS(ssr::enum_video_codec) = {
    {ssr::enum_video_codec::VIDEO_CODEC_H264, "h264"},
    {ssr::enum_video_codec::VIDEO_CODEC_VP8, "vp8"},
    {ssr::enum_video_codec::VIDEO_CODEC_THEORA, "theora"},
    {ssr::enum_video_codec::VIDEO_CODEC_OTHER, "other"},
};
ENUMSTRINGS(ssr::enum_audio_codec) = {
    {ssr::enum_audio_codec::AUDIO_CODEC_VORBIS, "vorbis"},
    {ssr::enum_audio_codec::AUDIO_CODEC_MP3, "mp3"},
    {ssr::enum_audio_codec::AUDIO_CODEC_AAC, "aac"},
    {ssr::enum_audio_codec::AUDIO_CODEC_UNCOMPRESSED, "uncompressed"},
    {ssr::enum_audio_codec::AUDIO_CODEC_OTHER, "other"},
};
//ENUMSTRINGS(ssr::enum_h264_preset) = {
//    {PageOutput::H264_PRESET_ULTRAFAST, "ultrafast"},
//    {PageOutput::H264_PRESET_SUPERFAST, "superfast"},
//    {PageOutput::H264_PRESET_VERYFAST, "veryfast"},
//    {PageOutput::H264_PRESET_FASTER, "faster"},
//    {PageOutput::H264_PRESET_FAST, "fast"},
//    {PageOutput::H264_PRESET_MEDIUM, "medium"},
//    {PageOutput::H264_PRESET_SLOW, "slow"},
//    {PageOutput::H264_PRESET_SLOWER, "slower"},
//    {PageOutput::H264_PRESET_VERYSLOW, "veryslow"},
//    {PageOutput::H264_PRESET_PLACEBO, "placebo"},
//};


ssrtools::ssrtools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ssrtools)
{
    ui->setupUi(this);
    setStyle();


//    mp->hide();
    Init();
    mp = new mypopup(this, parent);

}

ssrtools::~ssrtools()
{
    delete ui;
}

void ssrtools::setStyle()
{
    QString runPath = QCoreApplication::applicationDirPath();
    QFile file(runPath + "/qss/ssrtools.qss");
    qDebug() << "bybobbi: " << file.fileName();
    file.open(QFile::ReadOnly);
    QTextStream fileText(&file);
    QString stylesheet = fileText.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
}

void ssrtools::Init()
{


    options_show = false;

    m_grabbing = false;
    m_selecting_window = false;


    //record init
    m_output_started =false;

    //input
    m_buttongroup_video_area = new QButtonGroup;
    m_buttongroup_video_area->addButton(ui->m_radioButton_fullscreen, int(ssr::enum_video_area::VIDEO_AREA_SCREEN));
    m_buttongroup_video_area->addButton(ui->m_radioButton_fixed, int(ssr::enum_video_area::VIDEO_AREA_FIXED));
    m_buttongroup_video_area->addButton(ui->m_radioButton_cursor, int(ssr::enum_video_area::VIDEO_AREA_CURSOR));


    ui->m_spinbox_video_x->setRange(0, SSR_MAX_IMAGE_SIZE);
    ui->m_spinbox_video_x->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->m_spinbox_video_y->setRange(0, SSR_MAX_IMAGE_SIZE);
    ui->m_spinbox_video_y->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->m_spinbox_video_w->setRange(0, SSR_MAX_IMAGE_SIZE);
    ui->m_spinbox_video_w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->m_spinbox_video_h->setRange(0, SSR_MAX_IMAGE_SIZE);
    ui->m_spinbox_video_h->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(m_buttongroup_video_area, SIGNAL(buttonClicked(int)), SLOT(OnUpdateVideoAreaFields()));
    connect(ui->m_spinbox_video_x, SIGNAL(focusIn()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_x, SIGNAL(focusOut()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_x, SIGNAL(valueChanged(int)), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_y, SIGNAL(focusIn()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_y, SIGNAL(focusOut()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_y, SIGNAL(valueChanged(int)), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_w, SIGNAL(focusIn()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_w, SIGNAL(focusOut()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_w, SIGNAL(valueChanged(int)), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_h, SIGNAL(focusIn()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_h, SIGNAL(focusOut()), this, SLOT(OnUpdateRecordingFrame()));
    connect(ui->m_spinbox_video_h, SIGNAL(valueChanged(int)), this, SLOT(OnUpdateRecordingFrame()));


    //mp input
//    connect(mp->getUI()->m_comboBox_videores,
//    mp->InputInit(this);

    Output_init();
    //mp output
//    mp->OutputInit();


    LoadSettings();


}

void ssrtools::Output_init()
{
    m_containers = {
        ContainerData({"Matroska (MKV)", "matroska", QStringList({"mkv"}), tr("%1 files", "This appears in the file dialog, e.g. 'MP4 files'").arg("Matroska") + " (*.mkv)",
            {ssr::enum_video_codec::VIDEO_CODEC_H264, ssr::enum_video_codec::VIDEO_CODEC_VP8, ssr::enum_video_codec::VIDEO_CODEC_THEORA},
            {ssr::enum_audio_codec::AUDIO_CODEC_VORBIS, ssr::enum_audio_codec::AUDIO_CODEC_MP3,ssr::enum_audio_codec:: AUDIO_CODEC_AAC, ssr::enum_audio_codec::AUDIO_CODEC_UNCOMPRESSED}}),
        ContainerData({"MP4", "mp4", QStringList({"mp4"}), tr("%1 files", "This appears in the file dialog, e.g. 'MP4 files'").arg("MP4") + " (*.mp4)",
            {ssr::enum_video_codec::VIDEO_CODEC_H264},
            {ssr::enum_audio_codec::AUDIO_CODEC_VORBIS, ssr::enum_audio_codec::AUDIO_CODEC_MP3, ssr::enum_audio_codec::AUDIO_CODEC_AAC}}),
        ContainerData({"WebM", "webm", QStringList({"webm"}), tr("%1 files", "This appears in the file dialog, e.g. 'MP4 files'").arg("WebM") + " (*.webm)",
            {ssr::enum_video_codec::VIDEO_CODEC_VP8},
            {ssr::enum_audio_codec::AUDIO_CODEC_VORBIS}}),
        ContainerData({"OGG", "ogg", QStringList({"ogg"}), tr("%1 files", "This appears in the file dialog, e.g. 'MP4 files'").arg("OGG") + " (*.ogg)",
            {ssr::enum_video_codec::VIDEO_CODEC_THEORA},
            {ssr::enum_audio_codec::AUDIO_CODEC_VORBIS}}),
        ContainerData({tr("Other..."), "other", QStringList(), "", std::set<ssr::enum_video_codec>({}), std::set<ssr::enum_audio_codec>({})}),
    };

    m_video_codecs = {
        {"H.264"       , "libx264"  },
        {"VP8"         , "libvpx"   },
        {"Theora"      , "libtheora"},
        {tr("Other..."), "other"    },
    };
    m_audio_codecs = {
        {"Vorbis"          , "libvorbis"   },
        {"MP3"             , "libmp3lame"  },
        {"AAC"             , "libvo_aacenc"},
        {tr("Uncompressed"), "pcm_s16le"   },
        {tr("Other...")    , "other"       },
    };

    m_containers_av.clear();
#if SSR_USE_AV_MUXER_ITERATE
    const AVOutputFormat *format;
    void *format_opaque = NULL;
    while((format = av_muxer_iterate(&format_opaque)) != NULL) {
#else
    for(AVOutputFormat *format = av_oformat_next(NULL); format != NULL; format = av_oformat_next(format)) {
#endif

        if (format->video_codec == AV_CODEC_ID_NONE)
            continue;
        ContainerData c;
        c.name = format->long_name;
        c.avname = format->name;
        c.suffixes = QString(format->extensions).split(',', QString::SkipEmptyParts);
        if (c.suffixes.isEmpty()) {
            c.filter = "";
        } else {
            c.filter = tr("%1 files", "This appears in the file dialog, e.g. 'MP4 files'").arg(c.avname) + "(*." + c.suffixes[0];
            for (int i = 1; i < c.suffixes.size(); ++i) {
                c.suffixes[i] = c.suffixes[i].trimmed();// needed because libav/ffmpeg isn't very consistent when they say 'comma-separated'
                c.filter += "*." + c.suffixes[i];
            }
            c.filter += ")";
        }
        m_containers_av.push_back(c);
    }
    std::sort(m_containers_av.begin(), m_containers_av.end());

    //load AV codec list
    m_video_codecs_av.clear();
    m_audio_codecs_av.clear();
#if SSR_USE_AV_MUXER_ITERATE
    const AVCodec *codec;
    void *codec_opaque = NULL;
    while((codec = av_codec_iterate(&codec_opaque)) != NULL) {
#else
    for(AVCodec *codec = av_codec_next(NULL); codec != NULL; codec = av_codec_next(codec)) {
#endif
        if(!av_codec_is_encoder(codec))
            continue;
        if(codec->type == AVMEDIA_TYPE_VIDEO && VideoEncoder::AVCodecIsSupported(codec->name)) {
            VideoCodecData c;
            c.name = codec->long_name;
            c.avname = codec->name;
            m_video_codecs_av.push_back(c);
        }
        if(codec->type == AVMEDIA_TYPE_AUDIO && AudioEncoder::AVCodecIsSupported(codec->name)) {
            AudioCodecData c;
            c.name = codec->long_name;
            c.avname = codec->name;
            m_audio_codecs_av.push_back(c);
        }
    }
    std::sort(m_video_codecs_av.begin(), m_video_codecs_av.end());
    std::sort(m_audio_codecs_av.begin(), m_audio_codecs_av.end());
    if(m_containers_av.empty()) {
        Logger::LogError("[OutputInit] " + tr("Error: Could not find any suitable container in libavformat!"));
        throw LibavException();
    }
    if(m_video_codecs_av.empty()) {
        Logger::LogError("[OutputInit] " + tr("Error: Could not find any suitable video codec in libavcodec!"));
        throw LibavException();
    }
    if(m_audio_codecs_av.empty()) {
        Logger::LogError("[OutputInit] " + tr("Error: Could not find any suitable audio codec in libavcodec!"));
        throw LibavException();
    }


}

void ssrtools::LoadSettings()
{
    QSettings settings(CommandLineOptions::GetSettingsFile(), QSettings::IniFormat);

    LoadInputSettings(&settings);

}

void ssrtools::LoadInputSettings(QSettings *settings)
{
    LoadInputProfileSettings(settings);
}






void ssrtools::on_m_toolButton_options_clicked()
{
   QRect og = ui->m_toolButton_options->geometry();
   QPoint pos = this->pos();
   mp->move(og.x() + pos.x(), og.y() + pos.y() + 100);
   if (!options_show) {
       options_show = true;
       mp->show();
   } else {
       options_show = false;
       mp->hide();
   }
}


void ssrtools::on_m_pushButton_start_clicked()
{
    m_file_base = mp->GetFile();


    if (m_output_started) return;
    try {
        Logger::LogInfo("[Begin Record: StartOutput]" + tr("Starting output ..."));

        if (m_output_manager == NULL) {
            //set the file name
            m_output_settings.file = GetNewSegmentFile(m_file_base, m_add_timestamp);
            qDebug() << "[record debug] m_output_settings.file: "  << m_output_settings.file;

            //for X11 recording, update the video size (if possible)
            if (m_x11_input != NULL) {
                m_x11_input->GetCurrentSize(&m_video_in_width, &m_video_in_height);
            }

            // calculate the output width and height
//            if(m_video_scaling) {
                // Only even width and height is allowed because some pixel formats (e.g. YUV420) require this.
//                m_output_settings.video_width = m_video_scaled_width / 2 * 2;
//                m_output_settings.video_height = m_video_scaled_height / 2 * 2;
//            } else {
                // If the user did not explicitly select scaling, then don't force scaling just because the recording area is one pixel too large.
                // One missing row/column of pixels is probably better than a blurry video (and scaling is SLOW).
            m_video_in_width = m_video_in_width / 2 * 2;
            m_video_in_height = m_video_in_height / 2 * 2;
            m_output_settings.video_width = m_video_in_width;
            m_output_settings.video_height = m_video_in_height;
//            }

        //start the output
            m_output_manager.reset(new OutputManager(m_output_settings));

        } else {

            // start a new segment
            m_output_manager->GetSynchronizer()->NewSegment();
        }

        Logger::LogInfo("[PageRecord::StartOutput] " + tr("Started output."));

        m_output_started = true;
        m_recorded_something = true;
        UpdateSysTray();
        UpdateRecordButton();
        UpdateInput();

    } catch(...) {
        Logger::LogError("[PageRecord::StartOutput] " + tr("Error: Something went wrong during initialization."));
    }
}

void ssrtools::OnUpdateVideoAreaFields()
{

}


void ssrtools::OnUpdateRecordingFrame()
{
    if(ui->m_spinbox_video_x->hasFocus() || ui->m_spinbox_video_y->hasFocus() || ui->m_spinbox_video_w->hasFocus() || ui->m_spinbox_video_h->hasFocus()) {
        if(m_recording_frame == NULL)
            m_recording_frame.reset(new RecordingFrameWindow(this));
        QRect rect = MapToLogicalCoordinates(ValidateRubberBandRectangle(QRect(GetVideoX(), GetVideoY(), GetVideoW(), GetVideoH())));
        if(rect.isNull()) {
            m_recording_frame->hide();
        } else {
            m_recording_frame->setGeometry(rect);
            m_recording_frame->show();
        }
    } else {
        m_recording_frame.reset();
    }
}

void ssrtools::mousePressEvent(QMouseEvent *event)
{
    if (m_grabbing) {
        if (event->button() == Qt::LeftButton) {
            if (IsPlatformX11()) {
                QPoint mouse_physical = GetMousePhysicalCoordinates();
                if (m_selecting_window) {
                    // As expected, Qt does not provide any functions to find the window at a specific position, so I have to use Xlib directly.
                    // I'm not completely sure whether this is the best way to do this, but it appears to work. XQueryPointer returns the window
                    // currently below the mouse along with the mouse position, but apparently this may not work correctly when the mouse pointer
                    // is also grabbed (even though it works fine in my test), so I use XTranslateCoordinates instead. Originally I wanted to
                    // show the rubber band when the mouse hovers over a window (instead of having to click it), but this doesn't work correctly
                    // since X will simply return a handle the rubber band itself (even though it should be transparent to mouse events).
                    Window selected_window;
                    int x, y;
                    if (XTranslateCoordinates(QX11Info::display(), QX11Info::appRootWindow(), QX11Info::appRootWindow(), mouse_physical.x(), mouse_physical.y(), &x, &y, &selected_window)) {
                        XWindowAttributes attributes;
                        if (selected_window != None && XGetWindowAttributes(QX11Info::display(), selected_window, &attributes)) {
                            // naive outer/inner rectangle, this won't work for window decorations
                            m_select_window_outer_rect = QRect(attributes.x, attributes.y, attributes.width + 2 * attributes.border_width, attributes.height + 2 * attributes.border_width);
                            m_select_window_inner_rect = QRect(attributes.x + attributes.border_width, attributes.y + attributes.border_width, attributes.width, attributes.height);

                            // try to find the real window (rather than the decorations added by the window manager)
                            Window real_window = X11FindRealWindow(QX11Info::display(), selected_window);
                            if (real_window != None) {
                                Atom actual_type;
                                int actual_format;
                                unsigned long items, bytes_left;
                                long *data = NULL;
                                int result = XGetWindowProperty(QX11Info::display(), real_window, XInternAtom(QX11Info::display(), "_NET_FRAME_EXTENTS", true),
                                                                 0, 4, false, AnyPropertyType, &actual_type, &actual_format, &items, &bytes_left, (unsigned char**)&data);
                                if (result == Success) {
                                    if (items == 4 && bytes_left == 0 && actual_format == 32) { // format 32 means 'long', even if long is 64-bit ...
                                        Window child;
                                        // the attributes of the real window only store the *relative* position which is not what we need, so use XTranslateCoordinates again
                                        if (XTranslateCoordinates(QX11Info::display(), real_window, QX11Info::appRootWindow(), 0, 0, &x, &y, &child)
                                                && XGetWindowAttributes(QX11Info::display(), real_window, &attributes)) {
                                            //finally
                                            m_select_window_inner_rect = QRect(x, y, attributes.width, attributes.height);
                                            m_select_window_outer_rect = m_select_window_inner_rect.adjusted(-data[0], -data[2], data[1], data[3]);
                                        } else {
                                            // I doubt this will ever be needed, but do it anyway
                                            m_select_window_inner_rect = m_select_window_outer_rect.adjusted(data[0], data[2], -data[1], -data[3]);
                                        }
                                    }
                                }
                                if (data != NULL)
                                    XFree(data);
                            }

                             // pick the inner rectangle if the users clicks inside the window, or the outer rectangle otherwise
                            m_rubber_band_rect = (m_select_window_inner_rect.contains(mouse_physical)) ? m_select_window_inner_rect : m_select_window_outer_rect;
                            UpdateRubberBand();
                        }
                    }
                } else {
                    m_rubber_band_rect = QRect(mouse_physical, mouse_physical);
                    UpdateRubberBand();
                }

            }
        } else {
            StopGrabbing();
        }
        event->accept();
        return;
    }
    event->ignore();
}

void ssrtools::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_grabbing) {
        if(event->button() == Qt::LeftButton) {
            if(m_rubber_band != NULL) {
                SetVideoAreaFromRubberBand();
            }
        }
        StopGrabbing();
        event->accept();
        return;
    }
    event->ignore();
}

void ssrtools::mouseMoveEvent(QMouseEvent *event)
{
    if(m_grabbing) {
        if(m_rubber_band != NULL && IsPlatformX11()) {
            QPoint mouse_physical = GetMousePhysicalCoordinates();
            if(m_selecting_window) {
                // pick the inner rectangle if the user clicks inside the window, or the outer rectangle otherwise
                m_rubber_band_rect = (m_select_window_inner_rect.contains(mouse_physical))? m_select_window_inner_rect : m_select_window_outer_rect;
            } else {
                m_rubber_band_rect.setBottomRight(mouse_physical);
            }
            UpdateRubberBand();
        }
        event->accept();
        return;
    }
    event->ignore();
}

void ssrtools::keyPressEvent(QKeyEvent *event)
{
    if(m_grabbing) {
        if(event->key() == Qt::Key_Escape) {
            StopGrabbing();
            return;
        }
        event->accept();
        return;
    }
    event->ignore();
}

void ssrtools::SetVideoArea(ssr::enum_video_area area)
{
    QAbstractButton *b = m_buttongroup_video_area->button(int(area));
    if(b != NULL) b->setChecked(true);
}

//void ssrtools::SetVideoAreaScreen(unsigned int screen)
//{
//    ui->m_combobox_frate->setCurrentIndex(clamp(screen, 0u, (unsigned int) m_combobox_screens->count() - 1));
//}

void ssrtools::SetVideoX(unsigned int x)
{
    ui->m_spinbox_video_x->setValue(x);
}

void ssrtools::SetVideoY(unsigned int y)
{
    ui->m_spinbox_video_y->setValue(y);
}

void ssrtools::SetVideoW(unsigned int w)
{
    ui->m_spinbox_video_w->setValue(w);
}

void ssrtools::SetVideoH(unsigned int h)
{
    ui->m_spinbox_video_h->setValue(h);
}

unsigned int ssrtools::GetVideoX()
{
    return ui->m_spinbox_video_x->value();
}

unsigned int ssrtools::GetVideoY()
{
    return ui->m_spinbox_video_y->value();
}

unsigned int ssrtools::GetVideoW()
{
    return ui->m_spinbox_video_w->value();
}

unsigned int ssrtools::GetVideoH()
{
    return ui->m_spinbox_video_h->value();
}

void ssrtools::on_m_pushbutton_video_select_rectangle_clicked()
{
    m_selecting_window = false;
    StartGrabbing();
}

void ssrtools::on_m_pushbutton_video_select_window_clicked()
{
    m_selecting_window = true;
    StartGrabbing();
}

void ssrtools::LoadInputProfileSettings(QSettings *settings)
{
    //load settings
#if 0
    SetVideoArea(StringToEnum(settings->value("input/video_area", QString()).toString(), VIDEO_AREA_SCREEN));
#else
    ssr::enum_video_area area = StringToEnum(settings->value("input/video_area", QString()).toString(), ssr::enum_video_area::VIDEO_AREA_SCREEN);
    SetVideoArea(area);
#endif
//    SetVideoAreaScreen(settings->value("input/video_area_screen", 0).toUInt());

    SetVideoX(settings->value("input/video_x", 0).toUInt());
    SetVideoY(settings->value("input/video_y", 0).toUInt());
    SetVideoW(settings->value("input/video_w", 800).toUInt());
    SetVideoH(settings->value("input/video_h", 600).toUInt());
//    SetVideoFrameRate(settings->value("input/video_frame_rate", 30).toUInt());

    //update things
    OnUpdateRecordingFrame();
    OnUpdateVideoAreaFields();

}




void ssrtools::StartGrabbing()
{
    m_grabbing = true;
    if (m_selecting_window) {
        ui->m_pushbutton_video_select_window->setDown(true);
    } else {
        ui->m_pushbutton_video_select_rectangle->setDown(true);
    }
    this->lower();
    grabMouse(Qt::CrossCursor);
    grabKeyboard();
    setMouseTracking(true);
}

void ssrtools::StopGrabbing()
{
    m_rubber_band.reset();
    setMouseTracking(false);
    releaseKeyboard();
    releaseMouse();
    this->raise();
    this->activateWindow();
    if(m_selecting_window)
        ui->m_pushbutton_video_select_window->setDown(false);
    else
        ui->m_pushbutton_video_select_rectangle->setDown(false);
    m_grabbing = false;
}

void ssrtools::UpdateRubberBand()
{
    if(m_rubber_band == NULL)
        m_rubber_band.reset(new RecordingFrameWindow(this));
    QRect rect = MapToLogicalCoordinates(ValidateRubberBandRectangle(m_rubber_band_rect));
    if(rect.isNull()) {
        m_rubber_band->hide();
    } else {
        m_rubber_band->setGeometry(rect);
        m_rubber_band->show();
    }
}

void ssrtools::SetVideoAreaFromRubberBand()
{
    QRect r = m_rubber_band_rect.normalized();
    if(GetVideoArea() == ssr::enum_video_area::VIDEO_AREA_CURSOR) {
        SetVideoX(0);
        SetVideoY(0);
    } else {
        SetVideoX(r.x());
        SetVideoY(r.y());
    }
    SetVideoW(r.width());
    SetVideoH(r.height());
}
