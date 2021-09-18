#include "bt_com_if.h"

#include <corewidget.h>

BT_COM_IF::BT_COM_IF(QObject *parent) : QObject(parent)
{

    m_core = (Ui::CoreWidget*)parent;
    m_server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol,this);
    m_local = new QBluetoothLocalDevice(this);
    m_disc = new QBluetoothDeviceDiscoveryAgent(this);
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    m_serv_disc = new QBluetoothServiceDiscoveryAgent(this);

    connect(m_disc, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BT_COM_IF::onDiscover);
    connect(m_serv_disc, &QBluetoothServiceDiscoveryAgent::serviceDiscovered, this ,&BT_COM_IF::onServiceDiscovered);
    m_disc->start();
    m_serv_disc->start();

    connect(m_socket, &QBluetoothSocket::connected, this, &BT_COM_IF::onConnect);
}

void BT_COM_IF::connectModule()
{
    static const QString serv_uid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    QString msg = QString("Connecting to: %1 %2")
                    .arg(m_info.address().toString())
                    .arg(m_info.deviceUuid().toString())
                    ;

    qWarning() << msg;
    lg(msg);

    try {
        m_socket->connectToService(m_info.address(),QBluetoothUuid(serv_uid));

    }  catch (...) {

    }
}

void BT_COM_IF::transmitFrame()
{

}

void BT_COM_IF::onDiscover(const QBluetoothDeviceInfo &info)
{
    QString theName = info.name();
    if(discFilter.contains(theName)){
        m_info = info;
        emit canModuleFound(QString("can module found: %1").arg(theName));
        emit moduleAvailable(true);
    }
}

void BT_COM_IF::onServiceDiscovered(const QBluetoothServiceInfo &info)
{
    QString theName = info.device().name();

    if(discFilter.contains(theName)){
        m_serv_info = info;
        emit canModuleFound(QString("can module found: %1").arg(theName));
        emit moduleAvailable(true);
    }
}

void BT_COM_IF::onConnect()
{
    lg("connected");
    connected = true;
    connect(m_socket,&QBluetoothSocket::readyRead,this,&BT_COM_IF::onReadyRead);
}

void BT_COM_IF::onReadyRead()
{
    std::string bf = m_socket->readAll().toStdString();
    lg(QString::fromStdString(bf));
}

void BT_COM_IF::lg(QString msg)
{
    emit log(msg);
}
