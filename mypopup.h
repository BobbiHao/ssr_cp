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
    void InputInit(ssrtools *ssr);
    void OutputInit();
//    inline Ui::mypopup *getUI() {return ui;}

    void LoadScreenConfigurations();


private:
    Ui::mypopup *ui;
    ssrtools *ssr;
//    std::vector<ContainerData> m_containers, m_containers_av;

    QComboBox *m_combobox_container_av_not_shown;

    std::vector<ScreenLabelWindow*> m_screen_labels;


public slots:
    void OnUpdateVideoAreaFields();

private slots:
    void OnIdentifyScreens();
    void OnStopIdentifyScreens();

    void OnBrowse();


public:
    inline ssr::enum_container GetContainer();
    unsigned int GetContainerAV();
};

#endif // MYPOPUP_H
