#include "ssrtools.h"
#include "ui_ssrtools.h"
#include <QDebug>

#include <QFile>

ssrtools::ssrtools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ssrtools)
{
    ui->setupUi(this);
    setStyle();

    mp = new mypopup();
//    mp->hide();

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

    //input
    m_buttongroup_video_area = new QButtonGroup;
    m_buttongroup_video_area->addButton(ui->m_radioButton_fullscreen, VIDEO_AREA_SCREEN);
    m_buttongroup_video_area->addButton(ui->m_radioButton_fixed, VIDEO_AREA_FIXED);
    m_buttongroup_video_area->addButton(ui->m_radioButton_cursor, VIDEO_AREA_CURSOR);


    connect(m_buttongroup_video_area, SIGNAL(buttonClicked(int)), SLOT(OnUpdateVideoAreaFields()));



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
}

void ssrtools::OnUpdateVideoAreaFields()
{

}
