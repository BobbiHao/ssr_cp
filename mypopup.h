#ifndef MYPOPUP_H
#define MYPOPUP_H

#include <QWidget>

#include "Global.h"
#include "ssrtools.h"

namespace Ui {
class mypopup;
}


class mypopup : public QWidget
{
    Q_OBJECT

public:
    explicit mypopup(QWidget *parent = nullptr);
    ~mypopup();

    void InputInit();
    void OutputInit();

private:
    Ui::mypopup *ui;
//    ssrtools *ssr;
//    std::vector<ContainerData> m_containers, m_containers_av;

public slots:
    void OnUpdateVideoAreaFields();

private slots:
    void OnIdentifyScreens();
    void OnStopIdentifyScreens();

};

#endif // MYPOPUP_H
