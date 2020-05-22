#include "mypopup.h"
#include "ui_mypopup.h"

//#include "WidgetWrapper.h"

#include <QFileDialog>
#include <QGroupBox>

static ssrtools* ssr;

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

mypopup::~mypopup()
{
    delete ui;
}

void mypopup::InputInit()
{
    connect(ui->m_comboBox_videores, SIGNAL(activated(int)), this, SLOT(OnUpdateVideoAreaFields()));
    connect(ui->m_comboBox_videores, SIGNAL(popupShown()), this, SLOT(OnIdentifyScreens()));
    connect(ui->m_comboBox_videores, SIGNAL(popupHidden()), this, SLOT(OnStopIdentifyScreens()));
//    ui->m_comboBox_videores->addItem()


//    QGroupBox *groupbox_viedo = new QGroupBox();

}

void mypopup::OutputInit()
{

}

static std::vector<QRect> GetScreenGeometries() {
    std::vector<QRect> screen_geometries;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    for(QScreen *screen :  QApplication::screens()) {
        QRect geometry = screen->geometry();
        qreal ratio = screen->devicePixelRatio();
        screen_geometries.emplace_back(geometry.x(), geometry.y(), lrint((qreal) geometry.width() * ratio), lrint((qreal) geometry.height() * ratio));
    }
#else
    for(int i = 0; i < QApplication::desktop()->screenCount(); ++i) {
        screen_geometries.push_back(QApplication::desktop()->screenGeometry(i));
    }
#endif
    return screen_geometries;
}

static QRect CombineScreenGeometries(const std::vector<QRect>& screen_geometries) {
    QRect combined_geometry;
    for(const QRect &geometry : screen_geometries) {
        combined_geometry |= geometry;
    }
    return combined_geometry;
}

void mypopup::OnUpdateVideoAreaFields()
{
    switch(ssr->GetVideoArea()) {
    case VIDEO_AREA_SCREEN: {
        int sc = ui->m_comboBox_videores->currentIndex();
        std::vector<QRect> screen_geometries = GetScreenGeometries();
        QRect rect;
        if (sc > 0 && sc <= (int)screen_geometries.size()) {
            rect = screen_geometries[sc - 1];
        } else {
            rect = CombineScreenGeometries(screen_geometries);
        }
        break;
    }
    case VIDEO_AREA_FIXED: {
        break;
    }
    case VIDEO_AREA_CURSOR: {
        break;
    }
    default:
        break;
        }
}

void mypopup::OnIdentifyScreens()
{

}

void mypopup::OnStopIdentifyScreens()
{

}

