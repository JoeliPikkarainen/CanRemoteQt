#ifndef MODULECONTROLWIDGET_H
#define MODULECONTROLWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "src/bt_com_if.h"
#include "src/moduleapi.h"

class ModuleControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModuleControlWidget(BT_COM_IF* bt, ModuleApi* api ,QWidget *parent = nullptr);

public slots:
    void onCanRateReceived(COM_FRAME rxframe);

signals:

private slots:
    void request_get_canrate();
    void request_set_canrate();

private:
    BT_COM_IF *m_bt;
    ModuleApi* m_api;

    QVBoxLayout* mainVLine;

    QHBoxLayout* canRateControlLine;
    QLabel* canRateLabel;
    QPushButton* canRateGetBtn;
    QPushButton* canRateSetBtn;
    QLineEdit* canRateLineEdit;
    QLabel* cabRateQLabel;

};

#endif // MODULECONTROLWIDGET_H
