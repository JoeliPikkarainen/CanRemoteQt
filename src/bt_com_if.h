#ifndef BT_COM_IF_H
#define BT_COM_IF_H

#include <QtBluetooth>

#include <QObject>

#include "com_frame.h"

class BT_COM_IF : public QObject
{
    Q_OBJECT
public:
    explicit BT_COM_IF(QObject *parent = nullptr);

    QBluetoothDeviceDiscoveryAgent* m_disc;
    QBluetoothSocket* m_socket;

public slots:
    void connectModule();
    quint64 transmitFrame(COM_FRAME frame);
    void onDisconnectRequested();
    void onToggleStreamRequested();

signals:
    void canModuleFound(QString name);
    void moduleAvailable(bool available);
    void disconnected();

    void log(QString msg);
    void frameReceived(const QByteArray& frame);

private slots:
    void onDiscover(const QBluetoothDeviceInfo &info);
    void onConnect();
    void onReadyRead();

private:
    QList<QString> discFilter {"HC-05"};
    QBluetoothDeviceInfo m_info;
    QBluetoothServiceInfo m_serv_info;
    bool connected = false;
    void lg(QString msg);


};

#endif // BT_COM_IF_H
