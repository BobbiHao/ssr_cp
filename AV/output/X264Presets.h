#ifndef X264PRESETS_H
#define X264PRESETS_H
#include "Global.h"
#include <libavcodec/avcodec.h>

// This file was generated by 'x264-preset-translator.php', don't edit it.

#if !SSR_USE_AVCODEC_PRIVATE_PRESET

void X264Preset(AVCodecContext* cc, const char* preset);

void X264Preset_ultrafast(AVCodecContext* cc);
void X264Preset_superfast(AVCodecContext* cc);
void X264Preset_veryfast(AVCodecContext* cc);
void X264Preset_faster(AVCodecContext* cc);
void X264Preset_fast(AVCodecContext* cc);
void X264Preset_medium(AVCodecContext* cc);
void X264Preset_slow(AVCodecContext* cc);
void X264Preset_slower(AVCodecContext* cc);
void X264Preset_veryslow(AVCodecContext* cc);
void X264Preset_placebo(AVCodecContext* cc);

#endif


#endif // X264PRESETS_H