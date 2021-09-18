#include "bt_com_if.h"

#include <corewidget.h>

#include "com_frame.h"
#include "frameconverter.h"

BT_COM_IF::BT_COM_IF(QObject *parent) : QObject(parent)
{

    m_core = (Ui::CoreWidget*)parent;
    m_disc = new QBluetoothDeviceDiscoveryAgent(this);
    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(m_disc, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BT_COM_IF::onDiscover);
    m_disc->start();

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

void BT_COM_IF::onDisconnectRequested()
{
    QString log = QString("disconnecting from: %1 ").arg(m_socket->peerName());
    lg(log);


    try {
        m_socket->disconnectFromService();

    }  catch (...) {

    }

    log = QString("disconnected");
    lg(log);

    emit disconnected();
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


void BT_COM_IF::onConnect()
{
    lg("connected");
    connected = true;
    connect(m_socket,&QBluetoothSocket::readyRead,this,&BT_COM_IF::onReadyRead);
    m_disc->stop();
}

void BT_COM_IF::onReadyRead()
{
    QByteArray ba = m_socket->readAll();
    std::string bf = ba.toStdString();

    char* bfc = ba.data();
    int len_buff = ba.length();
    int len_data = len_buff - COM_FRAME::k_empty_size;
    uint8_t* bf8 = (uint8_t*)bfc;
    lg(FrameConverter::frameToHexString(ba));
}

void BT_COM_IF::lg(QString msg)
{
    emit log(msg);
}
