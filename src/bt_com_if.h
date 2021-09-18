#ifndef BT_COM_IF_H
#define BT_COM_IF_H

#include <QtBluetooth>

#include <QObject>
#include <corewidget.h>

class CoreWidget;
class BT_COM_IF : public QObject
{
    Q_OBJECT
public:
    explicit BT_COM_IF(QObject *parent = nullptr);

    QBluetoothDeviceDiscoveryAgent* m_disc;
    QBluetoothSocket* m_socket;

    Ui::CoreWidget* m_core;

public slots:
    void connectModule();
    void transmitFrame();
    void onDisconnectRequested();

signals:
    void canModuleFound(QString name);
    void moduleAvailable(bool available);
    void disconnected();

    void log(QString msg);

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
