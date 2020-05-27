#ifndef MYPOPUP_H
#define MYPOPUP_H

#include <QWidget>

#include "Global.h"
#include "ssrtools.h"
#include "WidgetWrapper.h"


namespace Ui {
class mypopup;
}

class ssrtools;

class mypopup : public QWidget
{
    Q_OBJECT

public:
    explicit mypopup(QWidget *parent = nullptr);
    explicit mypopup(ssrtools* ssr, QWidget *parent = nullptr);
    ~mypopup();

    void InputInit();
    void OutputInit();
//    inline Ui::mypopup *getUI() {return ui;}

    void LoadScreenConfigurations();
    void LoadAVProfileSettings(QSettings *settings);

public:

    QString GetFileProtocol();

private:
    Ui::mypopup *ui;
    ssrtools *ssr;
//    std::vector<ContainerData> m_containers, m_containers_av;
    std::vector<ScreenLabelWindow*> m_screen_labels;

    ssr::enum_container m_old_container;
    unsigned int m_old_container_av;

private:
    QLabel *m_label_container_av_not_shown;
    QComboBox *m_combobox_container_av_not_shown;
    QLineEdit *m_lineedit_file_not_shown;


public slots:
    void OnUpdateVideoAreaFields();
    void OnUpdateSuffixAndContainerFields();
    void OnUpdateContainerFields();

private slots:
    void OnIdentifyScreens();
    void OnStopIdentifyScreens();

    void OnBrowse();


public:
    inline ssr::enum_container GetContainer();
    unsigned int GetContainerAV();
    inline void SetContainer(ssr::enum_container container);
    inline void SetContainerAV(unsigned int container);
    inline QString GetFile() { return m_lineedit_file_not_shown->text(); }
    inline void SetFile(const QString& file) { m_lineedit_file_not_shown->setText(file); }

    void SetVideoCodec(ssr::enum_video_codec video_codec);

    void SetAudioCodec(ssr::enum_audio_codec audio_codec);

};

#endif // MYPOPUP_H
