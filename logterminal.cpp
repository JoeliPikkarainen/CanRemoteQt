#include "logterminal.h"
#include <QPen>
#include <QPainter>

LogTerminal::LogTerminal(QWidget *parent) : QLabel(parent)
{
    QString ss;
    ss = "background: black; color: green";
    this->setStyleSheet(ss);
    info.move(0,0);
    info.setText("info:");
}

void LogTerminal::append(QString msg)
{
    m_msgs.prepend(msg);
    if(m_msgs.count()> msg_buff_size){
        m_msgs.removeLast();
    }
    update();
}

void LogTerminal::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::green);
    p.setPen(pen);
    QFontMetrics fm(p.font());
    int fh = fm.height();

    int texty = this->height() - 5;

    foreach(QString msg, m_msgs){

        p.drawText(10,texty,msg);
        texty -= (fh + 5);
    }



}
