QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += AV AV/output common

LIBS += -lavutil -lavformat -lavcodec -lswscale

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
    AV/output/AudioEncoder.cpp \
    AV/output/BaseEncoder.cpp \
    AV/output/Muxer.cpp \
    AV/output/OutputManager.cpp \
    AV/output/Synchronizer.cpp \
    AV/output/VideoEncoder.cpp \
    AV/output/X264Presets.cpp \
    common/CPUFeatures.cpp \
    common/Logger.cpp \
    common/WidgetWrapper.cpp \
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
    AV/output/AudioEncoder.h \
    AV/output/BaseEncoder.h \
    AV/output/Muxer.h \
    AV/output/OutputManager.h \
    AV/output/Synchronizer.h \
    AV/output/VideoEncoder.h \
    AV/output/X264Presets.h \
    Global.h \
    common/CPUFeatures.h \
    common/Logger.h \
    common/MutexDataPair.h \
    common/QueueBuffer.h \
    common/TempBuffer.h \
    common/WidgetWrapper.h \
    mypopup.h \
    ssrtools.h

FORMS += \
    mypopup.ui \
    ssrtools.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
