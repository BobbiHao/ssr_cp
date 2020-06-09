QT       += core gui x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES +=	QT_DEPRECATED_WARNINGS \
                SSR_USE_FFMPEG_VERSIONS \
                SSR_USE_PULSEAUDIO
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += AV AV/output AV/input common GUI

LIBS += -lavutil -lavformat -lavcodec -lswscale -lX11 -lXext -lXfixes -lXinerama -lpulse

SOURCES += \
    AV/AVWrapper.cpp \
    AV/FastResamper_FirFilter_Fallback.cpp \
    AV/FastResampler.cpp \
    AV/FastScaler.cpp \
    AV/FastScaler_Convert_Fallback.cpp \
    AV/FastScaler_Convert_SSSE3.cpp \
    AV/FastScaler_Scale_Fallback.cpp \
    AV/FastScaler_Scale_Generic.cpp \
    AV/FastScaler_Scale_SSSE3.cpp \
    AV/SourceSink.cpp \
    AV/input/PulseAudioInput.cpp \
    AV/input/X11Input.cpp \
    AV/output/AudioEncoder.cpp \
    AV/output/BaseEncoder.cpp \
    AV/output/Muxer.cpp \
    AV/output/OutputManager.cpp \
    AV/output/Synchronizer.cpp \
    AV/output/SyncDiagram.cpp \
    AV/output/VideoEncoder.cpp \
    AV/output/X264Presets.cpp \
#    GUI/Input_Widgets.cpp \
#    GUI/Options_Widgets.cpp \
#    GUI/Output_Widgets.cpp \
    common/CPUFeatures.cpp \
    common/CommandLineOptions.cpp \
    common/Logger.cpp \
    common/WidgetWrapper.cpp \
    common/utils.cpp \
    main.cpp \
    mypopup.cpp \
    ssrtools.cpp

HEADERS += \
    AV/AVWrapper.h \
    AV/FastResampler.h \
    AV/FastResampler_FirFilter.h \
    AV/FastScaler.h \
    AV/FastScaler_Convert.h \
    AV/FastScaler_Scale.h \
    AV/FastScaler_Scale_Generic.h \
    AV/SampleCast.h \
    AV/SourceSink.h \
    AV/input/PulseAudioInput.h \
    AV/input/X11Input.h \
    AV/output/AudioEncoder.h \
    AV/output/BaseEncoder.h \
    AV/output/Muxer.h \
    AV/output/OutputManager.h \
    AV/output/Synchronizer.h \
    AV/output/SyncDiagram.h \
    AV/output/VideoEncoder.h \
    AV/output/X264Presets.h \
#    GUI/Input_Widgets.h \
#    GUI/Options_Widgets.h \
#    GUI/Output_Widgets.h \
    Global.h \
    common/CPUFeatures.h \
    common/CommandLineOptions.h \
    common/Enum.h \
    common/EnumStrings.h \
    common/Logger.h \
    common/MutexDataPair.h \
    common/QueueBuffer.h \
    common/SomeData.h \
    common/TempBuffer.h \
    common/WidgetWrapper.h \
    common/utils.h \
    mypopup.h \
    ssrtools.h

FORMS += \
    mypopup.ui \
    ssrtools.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
