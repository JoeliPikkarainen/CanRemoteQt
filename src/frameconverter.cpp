#include "frameconverter.h"

FrameConverter::FrameConverter(QObject *parent) : QObject(parent)
{

}

QString FrameConverter::frameToHexString(uint8_t *frame)
{
    QString retval;
    while (frame != nullptr) {
        QString hex = QString::number(*frame,16);
        QString apnd = QString(" %1 ").arg(hex);
        retval.append(apnd);
        frame++;
    }

    return retval;
}

QString FrameConverter::frameToHexString(const QByteArray &frame)
{
    QString retval;
    int size = frame.size();
    for(int i = 0; i < size ; i++){
        uint8_t c =     frame.at(i);
        QString hex = QString::number(c,16);
        if(hex.length() == 1){
            hex.prepend("0");
        }

        QString apnd = QString("%1 ").arg(hex);
        retval.append(apnd);
    }
    return retval;
}

QString FrameConverter::frameToTextualString(const QByteArray &frame)
{
    QString retval;

    int strlen = frame.at(4);
    if((COMMAND_BYTE)frame.at(3) == COMMAND_BYTE::INFO_STRING){

        retval = "INFO:";
        for(int i = 0; i < strlen; i++){
            retval.append(frame.at(i+5));
        }
    }

    return retval;
}
