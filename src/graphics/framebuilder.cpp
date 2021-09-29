#include "framebuilder.h"

FrameBuilder::FrameBuilder(QObject *parent) : QObject(parent)
{

}

COM_FRAME FrameBuilder::mkframe_Get_can_rate()
{
    COM_FRAME frame = mkframe_empty_frame();
    frame.m_ctb = COMMNAD_TYPE_BYTE::GET;
    frame.m_cb = COMMAND_BYTE::CAN_RATE;
    return frame;
}

COM_FRAME FrameBuilder::mkframe_Set_can_rate(uint16_t kbs)
{
    union{
        uint16_t u16;
        uint8_t u8[2];
    }un8t16;

    un8t16.u16 = kbs;
    uint8_t bf[2];
    bf[0] = un8t16.u8[0];
    bf[1] = un8t16.u8[1];

    COM_FRAME frame = COM_FRAME(
                SENDER_BYTE::SENDER_NULL_SENDER,
                COMMNAD_TYPE_BYTE::SET,
                COMMAND_BYTE::CAN_RATE,
                2,
                bf
                );

    return frame;
}

COM_FRAME FrameBuilder::mkframe_empty_frame()
{
    uint8_t bf[16];
    COM_FRAME frame = COM_FRAME(
                SENDER_BYTE::SENDER_NULL_SENDER,
                COMMNAD_TYPE_BYTE::GET,
                COMMAND_BYTE::CAN_RATE,
                0,
                bf
                );

    return frame;
}
