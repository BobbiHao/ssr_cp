#ifndef SSRTOOLS_H
#define SSRTOOLS_H

#include <QWidget>
#include "mypopup.h"
#include "OutputSettings.h"
#include <memory>
#include "OutputManager.h"
#include "Global.h"
#include "WidgetWrapper.h"

namespace Ui {
class ssrtools;
}

class mypopup;
class X11Input;

class ssrtools : public QWidget
{
    Q_OBJECT

public:
    explicit ssrtools(QWidget *parent = nullptr);
    ~ssrtools();

    void setStyle();

    void Init();

    void Output_init();


    void LoadSettings();

    void LoadInputSettings(QSettings* settings);

private slots:
    void on_m_toolButton_options_clicked();

    void on_m_pushButton_start_clicked();


    void on_m_pushbutton_video_select_rectangle_clicked();

    void on_m_pushbutton_video_select_window_clicked();

private:
    void LoadInputProfileSettings(QSettings* settings);

private:
    void StartGrabbing();
    void StopGrabbing();
    void UpdateRubberBand();
    void SetVideoAreaFromRubberBand();

public slots:
    void OnUpdateVideoAreaFields();
    void OnUpdateRecordingFrame();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::ssrtools *ui;
    mypopup *mp;
    QSettings settings;

    bool options_show;

    bool m_video_area_follow_fullscreen;
    unsigned int m_video_x, m_video_y, m_video_in_width, m_video_in_height;
    unsigned int m_video_frame_rate;

    bool m_video_record_cursor;

    bool m_audio_enabled;
    unsigned int m_auido_channels, m_audio_sample_rate;


    OutputSettings m_output_settings;
    std::unique_ptr<OutputManager> m_output_manager;

    QButtonGroup *m_buttongroup_video_area;

    QLabel *m_label_video_x, *m_label_video_y, *m_label_video_w, *m_label_video_h;

    bool m_grabbing, m_selecting_window;
    std::unique_ptr<RecordingFrameWindow>  m_rubber_band, m_recording_frame;
    QRect m_rubber_band_rect, m_select_window_outer_rect, m_select_window_inner_rect;


    std::unique_ptr<X11Input> m_x11_input;

private:
    //output
    struct ContainerData {
        QString name, avname;
        QStringList suffixes;
        QString filter;
        std::set<ssr::enum_video_codec> supported_video_codecs;
        std::set<ssr::enum_audio_codec> supported_audio_codecs;
        inline bool operator<(const ContainerData& other) const { return (avname < other.avname); }
    };
    struct VideoCodecData {
        QString name, avname;
        inline bool operator<(const VideoCodecData& other) const { return (avname < other.avname); }
    };
    struct AudioCodecData {
        QString name, avname;
        inline bool operator<(const AudioCodecData& other) const { return (avname < other.avname); }
    };
    std::vector<ContainerData> m_containers, m_containers_av;
    std::vector<VideoCodecData> m_video_codecs, m_video_codecs_av;
    std::vector<AudioCodecData> m_audio_codecs, m_audio_codecs_av;

private:
    //record
    bool m_output_started;
    ssr::enum_video_area m_video_area;

    QString m_file_base;
    bool m_add_timestamp;


public:
    inline ssr::enum_video_area GetVideoArea() { return (ssr::enum_video_area) clamp(m_buttongroup_video_area->checkedId(), 0, int(ssr::enum_video_area::VIDEO_AREA_COUNT) - 1); }

    void SetVideoArea(ssr::enum_video_area area);
//    void SetVideoAreaScreen(unsigned int screen);


    void SetVideoX(unsigned int x);
    void SetVideoY(unsigned int y);
    void SetVideoW(unsigned int w);
    void SetVideoH(unsigned int h);
    unsigned int GetVideoX();
    unsigned int GetVideoY();
    unsigned int GetVideoW();
    unsigned int GetVideoH();

    inline std::vector<ContainerData> GetContainers() { return m_containers; }
    inline std::vector<ContainerData> GetContainersAV() { return m_containers_av; }
    inline std::vector<VideoCodecData> GetVideoCodecs() { return m_video_codecs; }
    inline std::vector<AudioCodecData> GetAudioCodecs() { return m_audio_codecs; }

};

#endif // SSRTOOLS_H
