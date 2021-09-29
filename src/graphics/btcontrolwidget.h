#ifndef BTCONTROLWIDGET_H
#define BTCONTROLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QPushButton>
#include <QVBoxLayout>

#include "src/bt_com_if.h"

class BTControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BTControlWidget(QWidget *parent = nullptr, BT_COM_IF* bt = nullptr);

public slots:
    void setConnectEnabled(bool enable);
    void connectRequested();
    void disconnectRequested();
    void streamingToggledRequested();


signals:

private:

    QVBoxLayout* vboxConnections;
    QPushButton* conBtn;
    QPushButton* findBtn;
    QPushButton* dconBtn;
    QPushButton* streamToggleBtn;

    BT_COM_IF* m_bt;

};

#endif // BTCONTROLWIDGET_H
