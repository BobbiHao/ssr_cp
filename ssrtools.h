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

class ssrtools : public QWidget
{
    Q_OBJECT


public:
    explicit ssrtools(QWidget *parent = nullptr);
    ~ssrtools();

    void setStyle();

    void Init();

private slots:
    void on_m_toolButton_options_clicked();

    void on_m_pushButton_start_clicked();


public slots:
    void OnUpdateVideoAreaFields();

private:
    Ui::ssrtools *ui;
    mypopup *mp;

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

public:
    inline enum_video_area GetVideoArea() { return (enum_video_area) clamp(m_buttongroup_video_area->checkedId(), 0, VIDEO_AREA_COUNT - 1); }


};

#endif // SSRTOOLS_H
