#ifndef LOGTERMINAL_H
#define LOGTERMINAL_H

#include <QWidget>
#include <QPaintEvent>
#include <QLabel>
#include <QLayoutItem>

class LogTerminal : public QLabel
{
    Q_OBJECT
public:
    explicit LogTerminal(QWidget *parent = nullptr);

    void append(QString msg);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const int msg_buff_size = 30;
    QList<QString> m_msgs;
    QLabel info;

};

#endif // LOGTERMINAL_H
