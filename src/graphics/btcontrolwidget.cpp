#include "btcontrolwidget.h"

BTControlWidget::BTControlWidget(QWidget *parent) : QWidget(parent)
{

    findBtn = new QPushButton(this);
    findBtn->setText("FIND");

    conBtn = new QPushButton(this);
    conBtn->setText("CONNECT");
    conBtn->setEnabled(false);

    dconBtn = new QPushButton(this);
    dconBtn->setText("DISCONNECT");

    connect(conBtn, &QPushButton::clicked, this, &BTControlWidget::connectRequested);
    connect(dconBtn, &QPushButton::clicked, this, &BTControlWidget::disconnectRequested);

    vboxConnections = new QVBoxLayout(this);
    vboxConnections->addWidget(findBtn);
    vboxConnections->addWidget(conBtn);
    vboxConnections->addWidget(dconBtn);
}

void BTControlWidget::setConnectEnabled(bool enable)
{
    conBtn->setEnabled(enable);
}
