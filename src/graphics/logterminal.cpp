#include "logterminal.h"
#include <QPen>
#include <QPainter>

LogTerminal::LogTerminal(QWidget *parent) : QLabel(parent)
{
    QString ssbg;
    ssbg = "background: black; color: green";

    QString ssbtn;
    ssbtn = "background: green; color: black";

    this->setStyleSheet(ssbg);
    info.move(0,0);
    info.setText("info:");

    clearBtn = new QPushButton(this);
    clearBtn->setText("CLEAR");
    clearBtn->setStyleSheet(ssbtn);
    connect(clearBtn,&QPushButton::clicked,this,&LogTerminal::clear);
}

void LogTerminal::append(QString msg)
{
    m_msgs.prepend(msg);
    if(m_msgs.count()> msg_buff_size){
        m_msgs.removeLast();
    }
    update();
}

void LogTerminal::clear()
{
    m_msgs.clear();
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
