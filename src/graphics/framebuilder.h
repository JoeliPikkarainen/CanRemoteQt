#ifndef FRAMEBUILDER_H
#define FRAMEBUILDER_H

#include <QObject>

#include "com_frame.h"

class FrameBuilder : public QObject
{
    Q_OBJECT
public:
    explicit FrameBuilder(QObject *parent = nullptr);

    static COM_FRAME mkframe_Get_can_rate();
    static COM_FRAME mkframe_Set_can_rate(uint16_t kbs);

signals:

private:
    static COM_FRAME mkframe_empty_frame();

};

#endif // FRAMEBUILDER_H
