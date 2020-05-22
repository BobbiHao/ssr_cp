#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstddef>
#include <exception>
#include <mutex>
#include <cassert>
#include <vector>

#include <unistd.h>

#include <QtGui>
#include <QButtonGroup>
#include <QLabel>




extern "C" {
#include <libavutil/rational.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
#include <libavutil/mem.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
#include <libavutil/samplefmt.h>
}

enum enum_video_area {
    VIDEO_AREA_SCREEN,
    VIDEO_AREA_FIXED,
    VIDEO_AREA_CURSOR,
    VIDEO_AREA_COUNT
};



// simple function to do 16-byte alignment
inline size_t grow_align16(size_t size) {
    return (size_t) (size + 15) & ~((size_t) 15);
}

// convert weird types from libav/ffmpeg to doubles
inline double ToDouble(const AVRational& r) {
    return (double) r.num / (double) r.den;
}

class LibavException : public std::exception {
public:
    inline virtual const char * what() const throw() override {
        return "LibavException";
    }
};
class ResamplerException : public std::exception {
public:
    inline virtual const char* what() const throw() override {
        return "ResamplerException";
    }
};

template<typename T>
inline T clamp(T v, T lo, T hi) {
    assert(lo <= hi);
    if(v < lo)
        return lo;
    if(v > hi)
        return hi;
    return v;
}
template<> inline float clamp<float>(float v, float lo, float hi) {
    assert(lo <= hi);
    return fmin(fmax(v, lo), hi);
}
template<> inline double clamp<double>(double v, double lo, double hi) {
    assert(lo <= hi);
    return fmin(fmax(v, lo), hi);
}

// high resolution timer
inline int64_t hrt_time_micro() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t) ts.tv_sec * (uint64_t) 1000000 + (uint64_t) (ts.tv_nsec / 1000);
}



//#define SSR_USE_X86_ASM 1

// generic macro to test version numbers
#define TEST_MAJOR_MINOR(major, minor, required_major, required_minor) (major > required_major || (major == required_major && minor >= required_minor))
// test GCC version
#define TEST_GCC_VERSION(major, minor) TEST_MAJOR_MINOR(__GNUC__, __GNUC_MINOR__, major, minor)


#if SSR_USE_FFMPEG_VERSIONS
#define TEST_AV_VERSION(prefix, ffmpeg_major, ffmpeg_minor, libav_major, libav_minor) TEST_MAJOR_MINOR(prefix##_VERSION_MAJOR, prefix##_VERSION_MINOR, ffmpeg_major, ffmpeg_minor)
#else
#define TEST_AV_VERSION(prefix, ffmpeg_major, ffmpeg_minor, libav_major, libav_minor) TEST_MAJOR_MINOR(prefix##_VERSION_MAJOR, prefix##_VERSION_MINOR, libav_major, libav_minor)
#endif
// avcodec_encode_video2: lavc 54.2.100 / 54.1.0
#define SSR_USE_AVCODEC_ENCODE_VIDEO2              TEST_AV_VERSION(LIBAVCODEC, 54, 2, 54, 1)

#define SSR_USE_AVCODEC_PRIVATE_PRESET             TEST_AV_VERSION(LIBAVCODEC, 53, 8, 53, 8)

// av_codec_is_encoder: lavc 54.8.100 / 54.7.0
#define SSR_USE_AV_CODEC_IS_ENCODER                TEST_AV_VERSION(LIBAVCODEC, 54, 8, 54, 7)

// av_frame_alloc, av_frame_free: lavc 55.45.101 / 55.28.1
#define SSR_USE_AV_FRAME_ALLOC                     TEST_AV_VERSION(LIBAVCODEC, 55, 45, 55, 28)
// av_register_all deprecated: lavf 58.9.100 / ???
#define SSR_USE_AV_REGISTER_ALL_DEPRECATED         TEST_AV_VERSION(LIBAVFORMAT, 58, 9, 999, 999)

// avcodec_encode_audio2: lavc 53.56.105 / 53.34.0
#define SSR_USE_AVCODEC_ENCODE_AUDIO2              TEST_AV_VERSION(LIBAVCODEC, 53, 56, 53, 34)

// AVStream::codecpar: lavf 57.33.100 / 57.5.0
#define SSR_USE_AVSTREAM_CODECPAR                  TEST_AV_VERSION(LIBAVFORMAT, 57, 33, 57, 5)

// Maximum allowed image size (to avoid 32-bit integer overflow)
#define SSR_MAX_IMAGE_SIZE 20000


#endif // GLOBAL_H
