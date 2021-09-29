#ifndef FRAMECONVERTER_H
#define FRAMECONVERTER_H

#include <QObject>
#include <com_frame.h>

class FrameConverter : public QObject
{
    Q_OBJECT
public:
    explicit FrameConverter(QObject *parent = nullptr);

    static QString frameToHexString(uint8_t *frame);
    static QString frameToHexString(const QByteArray& frame);
    static QString frameToTextualString(const QByteArray& frame);

signals:

};

#endif // FRAMECONVERTER_H
