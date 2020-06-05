#ifndef OPTIONS_WIDGETS_H
#define OPTIONS_WIDGETS_H


#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "WidgetWrapper.h"

QT_BEGIN_NAMESPACE

class Options_Widgets
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *m_pushButton_storelocation;
    QLabel *label_2;
    QComboBox *m_comboBox_container;
    QLabel *label_3;
    QComboBox *m_comboBox_audiorate;
    QLabel *label_4;
    QComboBox *m_comboBox_videofrate;
    QLabel *label_5;
    QComboBoxWithSignal *m_comboBox_videores;
    QLabel *label_6;
    QComboBox *m_comboBox_video_codec;
    QLabel *label_7;
    QComboBox *m_comboBox_audio_codec;

    void setupUi(QWidget *mypopup)
    {
        if (mypopup->objectName().isEmpty())
            mypopup->setObjectName(QString::fromUtf8("mypopup"));
        mypopup->resize(142, 438);
        widget = new QWidget(mypopup);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 10, 102, 404));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        m_pushButton_storelocation = new QPushButton(widget);
        m_pushButton_storelocation->setObjectName(QString::fromUtf8("m_pushButton_storelocation"));

        verticalLayout->addWidget(m_pushButton_storelocation);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        m_comboBox_container = new QComboBox(widget);
        m_comboBox_container->setObjectName(QString::fromUtf8("m_comboBox_container"));
        m_comboBox_container->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(m_comboBox_container);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        m_comboBox_audiorate = new QComboBox(widget);
        m_comboBox_audiorate->setObjectName(QString::fromUtf8("m_comboBox_audiorate"));

        verticalLayout->addWidget(m_comboBox_audiorate);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        m_comboBox_videofrate = new QComboBox(widget);
        m_comboBox_videofrate->setObjectName(QString::fromUtf8("m_comboBox_videofrate"));

        verticalLayout->addWidget(m_comboBox_videofrate);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        m_comboBox_videores = new QComboBoxWithSignal(widget);
        m_comboBox_videores->setObjectName(QString::fromUtf8("m_comboBox_videores"));

        verticalLayout->addWidget(m_comboBox_videores);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        m_comboBox_video_codec = new QComboBox(widget);
        m_comboBox_video_codec->setObjectName(QString::fromUtf8("m_comboBox_video_codec"));

        verticalLayout->addWidget(m_comboBox_video_codec);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout->addWidget(label_7);

        m_comboBox_audio_codec = new QComboBox(widget);
        m_comboBox_audio_codec->setObjectName(QString::fromUtf8("m_comboBox_audio_codec"));

        verticalLayout->addWidget(m_comboBox_audio_codec);


        retranslateUi(mypopup);

        QMetaObject::connectSlotsByName(mypopup);
    } // setupUi

    void retranslateUi(QWidget *mypopup)
    {
        mypopup->setWindowTitle(QApplication::translate("mypopup", "Form", nullptr));
        label->setText(QApplication::translate("mypopup", "store location", nullptr));
        m_pushButton_storelocation->setText(QApplication::translate("mypopup", "...", nullptr));
        label_2->setText(QApplication::translate("mypopup", "container", nullptr));
        label_3->setText(QApplication::translate("mypopup", "audio byte rate", nullptr));
        label_4->setText(QApplication::translate("mypopup", "video frate", nullptr));
        label_5->setText(QApplication::translate("mypopup", "video res", nullptr));
        label_6->setText(QApplication::translate("mypopup", "video codec", nullptr));
        label_7->setText(QApplication::translate("mypopup", "audio codec", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mypopup: public Options_Widgets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPTIONS_WIDGETS_H
