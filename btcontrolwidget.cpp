#include "btcontrolwidget.h"

BTControlWidget::BTControlWidget(QWidget *parent) : QWidget(parent)
{

    findBtn = new QPushButton(this);
    findBtn->setText("FIND");

    conBtn = new QPushButton(this);
    conBtn->setText("CONNECT");
    conBtn->setEnabled(false);

    connect(conBtn, &QPushButton::clicked, this, &BTControlWidget::connectRequested);
}

void BTControlWidget::setConnectEnabled(bool enable)
{
    conBtn->setEnabled(enable);
}
