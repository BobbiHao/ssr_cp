/********************************************************************************
** Form generated from reading UI file 'mypopup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPOPUP_H
#define UI_MYPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mypopup
{
public:
    QWidget *widget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *m_pushButton_storelocation;
    QLabel *label_2;
    QComboBox *m_comboBox_container;
    QLabel *label_3;
    QComboBox *m_comboBox_audiorate;
    QLabel *label_4;
    QComboBox *m_comboBox_videofrate;
    QLabel *label_5;
    QComboBox *m_comboBox_videores;
    QLabel *label;

    void setupUi(QWidget *mypopup)
    {
        if (mypopup->objectName().isEmpty())
            mypopup->setObjectName(QString::fromUtf8("mypopup"));
        mypopup->resize(104, 296);
        widget = new QWidget(mypopup);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 101, 291));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 95, 252));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_pushButton_storelocation = new QPushButton(layoutWidget);
        m_pushButton_storelocation->setObjectName(QString::fromUtf8("m_pushButton_storelocation"));

        verticalLayout->addWidget(m_pushButton_storelocation);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        m_comboBox_container = new QComboBox(layoutWidget);
        m_comboBox_container->setObjectName(QString::fromUtf8("m_comboBox_container"));
        m_comboBox_container->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(m_comboBox_container);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        m_comboBox_audiorate = new QComboBox(layoutWidget);
        m_comboBox_audiorate->setObjectName(QString::fromUtf8("m_comboBox_audiorate"));

        verticalLayout->addWidget(m_comboBox_audiorate);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        m_comboBox_videofrate = new QComboBox(layoutWidget);
        m_comboBox_videofrate->setObjectName(QString::fromUtf8("m_comboBox_videofrate"));

        verticalLayout->addWidget(m_comboBox_videofrate);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        m_comboBox_videores = new QComboBox(layoutWidget);
        m_comboBox_videores->setObjectName(QString::fromUtf8("m_comboBox_videores"));

        verticalLayout->addWidget(m_comboBox_videores);

        label = new QLabel(mypopup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 81, 18));

        retranslateUi(mypopup);

        QMetaObject::connectSlotsByName(mypopup);
    } // setupUi

    void retranslateUi(QWidget *mypopup)
    {
        mypopup->setWindowTitle(QApplication::translate("mypopup", "Form", nullptr));
        m_pushButton_storelocation->setText(QApplication::translate("mypopup", "...", nullptr));
        label_2->setText(QApplication::translate("mypopup", "container", nullptr));
        label_3->setText(QApplication::translate("mypopup", "audio byte rate", nullptr));
        label_4->setText(QApplication::translate("mypopup", "video frate", nullptr));
        label_5->setText(QApplication::translate("mypopup", "video res", nullptr));
        label->setText(QApplication::translate("mypopup", "store location", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mypopup: public Ui_mypopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPOPUP_H
