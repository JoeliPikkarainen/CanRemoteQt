#include "moduleapi.h"
#include "com_frame.h"

ModuleApi::ModuleApi(BT_COM_IF *bt, QObject *parent) : QObject(parent), m_bt(bt)
{

}

void ModuleApi::start()
{
    connect(m_bt,&BT_COM_IF::frameReceived,this, &ModuleApi::onFrameReceived);
}

void ModuleApi::stop()
{
    disconnect(m_bt,&BT_COM_IF::frameReceived,this, &ModuleApi::onFrameReceived);
}

void ModuleApi::transmitFrame(COM_FRAME txframe)
{
    m_bt->transmitFrame(txframe);
}

void ModuleApi::onFrameReceived(const QByteArray &frame)
{
    COM_FRAME comframe;
    comframe.fromByteArray((uint8_t*)frame.data(),frame.length());

    //emit frame_received_ANY(comframe);

    if(comframe.m_cb == COMMAND_BYTE::SYN){
        emit frame_received_SYN(comframe);
    }
    else if(comframe.m_cb == COMMAND_BYTE::ACK){

    }
    else if(comframe.m_cb == COMMAND_BYTE::CAN_FRAME){

    }
    else if(comframe.m_cb == COMMAND_BYTE::CAN_FRAME_DUMMY){

    }
    else if(comframe.m_cb == COMMAND_BYTE::STATUS_REQ){

    }
    else if(comframe.m_cb == COMMAND_BYTE::STATUS_ANS){

    }
    else if(comframe.m_cb == COMMAND_BYTE::CAN_RATE){
        emit frame_received_CANRATE(comframe);
    }
    else if(comframe.m_cb == COMMAND_BYTE::NULL_COMMAND_BYTE){

    }
    else{
        emit frame_received_UNDEFINED(comframe);
    }
}
