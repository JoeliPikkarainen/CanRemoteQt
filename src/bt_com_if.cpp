#include "bt_com_if.h"

#include <corewidget.h>

#include "com_frame.h"
#include "frameconverter.h"

BT_COM_IF::BT_COM_IF(QObject *parent) : QObject(parent)
{

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

quint64 BT_COM_IF::transmitFrame(COM_FRAME frame)
{
    int len = 0;
    uint8_t bf[64];
    frame.toByteArray(bf,len);


    QByteArray ba = QByteArray((const char*)bf,len);
    lg(QString("> %1").arg(FrameConverter::frameToHexString(ba)));
    return m_socket->write((char*)bf,len);
}



void BT_COM_IF::onDisconnectRequested()
{
    QString log = QString("disconnecting from: %1 ").arg(m_socket->peerName());
    lg(log);

    disconnect(m_socket,&QBluetoothSocket::readyRead,this,&BT_COM_IF::onReadyRead);

    try {
        m_socket->disconnectFromService();

    }  catch (...) {

    }

    log = QString("disconnected");
    lg(log);

    emit disconnected();
}

void BT_COM_IF::onToggleStreamRequested()
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


void BT_COM_IF::onConnect()
{
    lg("connected");
    connected = true;
    connect(m_socket,&QBluetoothSocket::readyRead,this,&BT_COM_IF::onReadyRead);
    m_disc->stop();
}

void BT_COM_IF::onReadyRead()
{
    QByteArray ba;
    for(int i = 0; i < COM_FRAME::k_header_size -1;i++){
        char c;
        int rode = m_socket->read(&c,1);
        if(rode != 1)
            return;
        ba.append(c);
    }
    char payloadlength;
    m_socket->read(&payloadlength,1);
    ba.append(payloadlength);

    for(int i = 0; i < payloadlength+1;i++){
        char c;
        int rode = m_socket->read(&c,1);
        if(rode != 1)
            return;
        ba.append(c);
    }
    std::string bf = ba.toStdString();

    emit frameReceived(ba);
    lg(QString("< %1 %2")
       .arg(FrameConverter::frameToHexString(ba))
       .arg(FrameConverter::frameToTextualString(ba))
       );

    onReadyRead();
}

void BT_COM_IF::lg(QString msg)
{
    emit log(msg);
}
