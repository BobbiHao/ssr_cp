/********************************************************************************
** Form generated from reading UI file 'ssrtools.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SSRTOOLS_H
#define UI_SSRTOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ssrtools
{
public:
    QToolButton *m_toolButton_options;
    QPushButton *m_pushButton_start;
    QRadioButton *m_radioButton_fullscreen;
    QRadioButton *m_radioButton_fixed;
    QRadioButton *m_radioButton_cursor;
    QLabel *m_label_video_x;
    QLabel *m_label_video_y;
    QLabel *m_label_video_width;
    QLabel *m_label_video_h;
    QLabel *label;
    QSpinBox *m_spinbox_video_x;
    QSpinBox *m_spinbox_video_y;
    QSpinBox *m_spinbox_video_w;
    QSpinBox *m_spinbox_video_h;
    QPushButton *m_pushbutton_video_select_rectangle;
    QPushButton *m_pushbutton_video_select_window;

    void setupUi(QWidget *ssrtools)
    {
        if (ssrtools->objectName().isEmpty())
            ssrtools->setObjectName(QString::fromUtf8("ssrtools"));
        ssrtools->resize(515, 341);
        m_toolButton_options = new QToolButton(ssrtools);
        m_toolButton_options->setObjectName(QString::fromUtf8("m_toolButton_options"));
        m_toolButton_options->setGeometry(QRect(320, 160, 51, 25));
        m_pushButton_start = new QPushButton(ssrtools);
        m_pushButton_start->setObjectName(QString::fromUtf8("m_pushButton_start"));
        m_pushButton_start->setGeometry(QRect(380, 160, 80, 26));
        m_radioButton_fullscreen = new QRadioButton(ssrtools);
        m_radioButton_fullscreen->setObjectName(QString::fromUtf8("m_radioButton_fullscreen"));
        m_radioButton_fullscreen->setGeometry(QRect(30, 160, 96, 24));
        m_radioButton_fixed = new QRadioButton(ssrtools);
        m_radioButton_fixed->setObjectName(QString::fromUtf8("m_radioButton_fixed"));
        m_radioButton_fixed->setGeometry(QRect(140, 160, 96, 24));
        m_radioButton_cursor = new QRadioButton(ssrtools);
        m_radioButton_cursor->setObjectName(QString::fromUtf8("m_radioButton_cursor"));
        m_radioButton_cursor->setGeometry(QRect(210, 160, 96, 24));
        m_label_video_x = new QLabel(ssrtools);
        m_label_video_x->setObjectName(QString::fromUtf8("m_label_video_x"));
        m_label_video_x->setGeometry(QRect(40, 40, 55, 18));
        m_label_video_y = new QLabel(ssrtools);
        m_label_video_y->setObjectName(QString::fromUtf8("m_label_video_y"));
        m_label_video_y->setGeometry(QRect(140, 30, 55, 18));
        m_label_video_width = new QLabel(ssrtools);
        m_label_video_width->setObjectName(QString::fromUtf8("m_label_video_width"));
        m_label_video_width->setGeometry(QRect(30, 80, 55, 18));
        m_label_video_h = new QLabel(ssrtools);
        m_label_video_h->setObjectName(QString::fromUtf8("m_label_video_h"));
        m_label_video_h->setGeometry(QRect(150, 80, 55, 18));
        label = new QLabel(ssrtools);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 60, 71, 21));
        m_spinbox_video_x = new QSpinBox(ssrtools);
        m_spinbox_video_x->setObjectName(QString::fromUtf8("m_spinbox_video_x"));
        m_spinbox_video_x->setGeometry(QRect(70, 30, 42, 27));
        m_spinbox_video_x->setMaximum(2000);
        m_spinbox_video_y = new QSpinBox(ssrtools);
        m_spinbox_video_y->setObjectName(QString::fromUtf8("m_spinbox_video_y"));
        m_spinbox_video_y->setGeometry(QRect(200, 30, 42, 27));
        m_spinbox_video_w = new QSpinBox(ssrtools);
        m_spinbox_video_w->setObjectName(QString::fromUtf8("m_spinbox_video_w"));
        m_spinbox_video_w->setGeometry(QRect(80, 80, 42, 27));
        m_spinbox_video_h = new QSpinBox(ssrtools);
        m_spinbox_video_h->setObjectName(QString::fromUtf8("m_spinbox_video_h"));
        m_spinbox_video_h->setGeometry(QRect(200, 80, 42, 27));
        m_pushbutton_video_select_rectangle = new QPushButton(ssrtools);
        m_pushbutton_video_select_rectangle->setObjectName(QString::fromUtf8("m_pushbutton_video_select_rectangle"));
        m_pushbutton_video_select_rectangle->setGeometry(QRect(129, 210, 91, 26));
        m_pushbutton_video_select_window = new QPushButton(ssrtools);
        m_pushbutton_video_select_window->setObjectName(QString::fromUtf8("m_pushbutton_video_select_window"));
        m_pushbutton_video_select_window->setGeometry(QRect(230, 210, 91, 26));

        retranslateUi(ssrtools);

        QMetaObject::connectSlotsByName(ssrtools);
    } // setupUi

    void retranslateUi(QWidget *ssrtools)
    {
        ssrtools->setWindowTitle(QApplication::translate("ssrtools", "Form", nullptr));
        m_toolButton_options->setText(QApplication::translate("ssrtools", "option", nullptr));
        m_pushButton_start->setText(QApplication::translate("ssrtools", "start", nullptr));
        m_radioButton_fullscreen->setText(QApplication::translate("ssrtools", "fullscreen", nullptr));
        m_radioButton_fixed->setText(QApplication::translate("ssrtools", "fixed", nullptr));
        m_radioButton_cursor->setText(QApplication::translate("ssrtools", "cursor", nullptr));
        m_label_video_x->setText(QApplication::translate("ssrtools", "Left", nullptr));
        m_label_video_y->setText(QApplication::translate("ssrtools", "Top", nullptr));
        m_label_video_width->setText(QApplication::translate("ssrtools", "Width", nullptr));
        m_label_video_h->setText(QApplication::translate("ssrtools", "Height", nullptr));
        label->setText(QApplication::translate("ssrtools", "VideoFrate", nullptr));
        m_pushbutton_video_select_rectangle->setText(QApplication::translate("ssrtools", "select rectangle", nullptr));
        m_pushbutton_video_select_window->setText(QApplication::translate("ssrtools", "select window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ssrtools: public Ui_ssrtools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SSRTOOLS_H
