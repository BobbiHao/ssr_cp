#include "WidgetWrapper.h"

WidgetWrapper::WidgetWrapper()
{

}

QComboBoxWithSignal::QComboBoxWithSignal(QWidget* parent)
    : QComboBox(parent) {}

void QComboBoxWithSignal::showPopup() {
    emit popupShown();
    QComboBox::showPopup();
}

void QComboBoxWithSignal::hidePopup() {
    emit popupHidden();
    QComboBox::hidePopup();
}
