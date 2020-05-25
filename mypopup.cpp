#include "mypopup.h"
#include "ui_mypopup.h"

//#include "WidgetWrapper.h"

#include <QFileDialog>
#include <QGroupBox>

#include "utils.h"

//static ssrtools* ssr;

mypopup::mypopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mypopup)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);

    ssr = static_cast<ssrtools*>(parent);

    InputInit();

    OutputInit();

}

mypopup::mypopup(ssrtools *ssr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mypopup)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);

    this->ssr = static_cast<ssrtools*>(ssr);

    InputInit();

    OutputInit();

}

mypopup::~mypopup()
{
    delete ui;
}

void mypopup::InputInit()
{
//    connect(ui->m_comboBox_videores, SIGNAL(activated(int)), this, SLOT(OnUpdateVideoAreaFields()));
//    connect(ui->m_comboBox_videores, SIGNAL(popupShown()), this, SLOT(OnIdentifyScreens()));
//    connect(ui->m_comboBox_videores, SIGNAL(popupHidden()), this, SLOT(OnStopIdentifyScreens()));
//    ui->m_comboBox_videores->addItem()


//    QGroupBox *groupbox_viedo = new QGroupBox();

}

void mypopup::InputInit(ssrtools *ssr)
{

    connect(ui->m_comboBox_videores, SIGNAL(activated(int)), this, SLOT(OnUpdateVideoAreaFields()));
    connect(ui->m_comboBox_videores, SIGNAL(popupShown()), this, SLOT(OnIdentifyScreens()));
    connect(ui->m_comboBox_videores, SIGNAL(popupHidden()), this, SLOT(OnStopIdentifyScreens()));
    LoadScreenConfigurations();
}

void mypopup::OutputInit()
{
//    connect(ui->m_pushButton_storelocation, SIGNAL(clicked()), this, SLOT(OnBrowse()));
    m_combobox_container_av_not_shown = new QComboBox;
}

void mypopup::LoadScreenConfigurations()
{
    std::vector<QRect> screen_geometries = GetScreenGeometries();
    QRect combined_geometry = CombineScreenGeometries(screen_geometries);
    ui->m_comboBox_videores->clear();
    ui->m_comboBox_videores->addItem(tr("All screens: %1x%2", "This appears in the screen selection combobox")
                                .arg(combined_geometry.width()).arg(combined_geometry.height()));
    for(size_t i = 0; i < screen_geometries.size(); ++i) {
        QRect &geometry = screen_geometries[i];
        ui->m_comboBox_videores->addItem(tr("Screen %1: %2x%3 at %4,%5", "This appears in the screen selection combobox")
                                    .arg(i + 1).arg(geometry.width()).arg(geometry.height()).arg(geometry.x()).arg(geometry.y()));
    }
    // update the video x/y/w/h in case the position or size of the selected screen changed
//    OnUpdateVideoAreaFields();
}

void mypopup::OnUpdateVideoAreaFields()
{
    switch(ssr->GetVideoArea()) {
    case ssr::enum_video_area::VIDEO_AREA_SCREEN: {
        int sc = ui->m_comboBox_videores->currentIndex();
        std::vector<QRect> screen_geometries = GetScreenGeometries();
        QRect rect;
        if (sc > 0 && sc <= (int)screen_geometries.size()) {
            rect = screen_geometries[sc - 1];
        } else {
            rect = CombineScreenGeometries(screen_geometries);
        }
        ssr->SetVideoX(rect.left());
        ssr->SetVideoY(rect.top());
        ssr->SetVideoW(rect.width());
        ssr->SetVideoH(rect.height());
        break;
    }
    case ssr::enum_video_area::VIDEO_AREA_FIXED: {
        break;
    }
    case ssr::enum_video_area::VIDEO_AREA_CURSOR: {
        break;
    }
    default:
        break;
        }
}

void mypopup::OnIdentifyScreens()
{
    OnStopIdentifyScreens();
    std::vector<QRect> screen_geometries = GetScreenGeometries();
    for (size_t i = 0; i < screen_geometries.size(); ++i) {
        QRect &rect = screen_geometries[i];
        ScreenLabelWindow *label = new ScreenLabelWindow(this, tr("Screen %1", "This appears in the screen labels").arg(i + 1));
        label->move(rect.x(), rect.y());
        label->show();
         m_screen_labels.push_back(label);
    }
}

void mypopup::OnStopIdentifyScreens()
{
    for (unsigned int i = 0; i < m_screen_labels.size(); ++i) {
        delete m_screen_labels[i];
    }
    m_screen_labels.clear();
}

void mypopup::OnBrowse()
{
    QString filters;
    auto ssr_containers = ssr->GetContainers();
    for (int i = 0; i < int(ssr::enum_container::CONTAINER_OTHER); ++i) {
        if (i != 0)
            filters += ssr_containers[i].filter;
    }

    auto ssr_containers_av = ssr->GetContainersAV();
    for (unsigned int i = 0; i < ssr_containers_av.size(); ++i) {
        if (!ssr_containers_av[i].filter.isEmpty())
            filters += ";;" + ssr_containers_av[i].filter;
    }

    ssr::enum_container container = GetContainer();
    unsigned int container_av = GetContainerAV();
    QString selected_filter = (container == ssr::enum_container::CONTAINER_OTHER) ?
                ssr->GetContainersAV()[container_av].filter : ssr->GetContainers()[int(container)].filter;
    QString selected_file = QFileDialog::getSaveFileName(this, tr("Save recording as"),
                                                         GetFile(), filters, &selected_filter, QFileDialog::DontConfirmOverwrite);

}

ssr::enum_container mypopup::GetContainer()
{
    return (ssr::enum_container) clamp(ui->m_comboBox_container->currentIndex(), 0, int(ssr::enum_container::CONTAINER_COUNT) - 1);
}

#if 1
unsigned int mypopup::GetContainerAV()
{
    return clamp(m_combobox_container_av_not_shown->currentIndex(), 0, int(ssr->GetContainersAV().size()) - 1);
}
#endif

