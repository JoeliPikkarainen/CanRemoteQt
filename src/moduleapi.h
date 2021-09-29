#ifndef MODULEAPI_H
#define MODULEAPI_H

#include <QObject>

#include "bt_com_if.h"

class ModuleApi : public QObject
{
    Q_OBJECT
public:
    explicit ModuleApi(BT_COM_IF* bt, QObject *parent = nullptr);
    void start();
    void stop();

public slots:
    void transmitFrame(COM_FRAME txframe);

signals:
    void frame_received_ANY(const COM_FRAME& frame);
    void frame_received_SYN(const COM_FRAME& frame);
    void frame_received_CANRATE(const COM_FRAME& frame);
    void frame_received_UNDEFINED(const COM_FRAME& frame);

private slots:
    void onFrameReceived(const QByteArray& frame);

private:
    BT_COM_IF* m_bt;


};

#endif // MODULEAPI_H
