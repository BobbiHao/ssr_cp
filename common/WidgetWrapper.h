#ifndef WIDGETWRAPPER_H
#define WIDGETWRAPPER_H

#include <QComboBox>


class QComboBoxWithSignal : public QComboBox {
    Q_OBJECT

public:
    QComboBoxWithSignal(QWidget* parent);

    virtual void showPopup() override;
    virtual void hidePopup() override;

signals:
    void popupShown();
    void popupHidden();

};

class WidgetWrapper
{
public:
    WidgetWrapper();
};

#endif // WIDGETWRAPPER_H
