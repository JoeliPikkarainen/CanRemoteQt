#ifndef LOGTERMINAL_H
#define LOGTERMINAL_H

#include <QWidget>
#include <QPaintEvent>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>

class LogTerminal : public QLabel
{
    Q_OBJECT
public:
    explicit LogTerminal(QWidget *parent = nullptr);

    void append(QString msg);
    void clear();

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const int msg_buff_size = 30;
    QList<QString> m_msgs;
    QLabel info;
    QPushButton* clearBtn;

};

#endif // LOGTERMINAL_H
