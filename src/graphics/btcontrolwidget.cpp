#include "btcontrolwidget.h"

BTControlWidget::BTControlWidget(QWidget *parent, BT_COM_IF *bt) : QWidget(parent)
{

    m_bt = bt;

    findBtn = new QPushButton(this);
    findBtn->setText("FIND");

    conBtn = new QPushButton(this);
    conBtn->setText("CONNECT");
    conBtn->setEnabled(false);

    dconBtn = new QPushButton(this);
    dconBtn->setText("DISCONNECT");

    streamToggleBtn = new QPushButton(this);
    streamToggleBtn->setText("STREAM START");

    connect(conBtn, &QPushButton::clicked, this, &BTControlWidget::connectRequested);
    connect(dconBtn, &QPushButton::clicked, this, &BTControlWidget::disconnectRequested);
    connect(streamToggleBtn, &QPushButton::clicked, this, &BTControlWidget::streamingToggledRequested);
    connect(bt, &BT_COM_IF::moduleAvailable, this, &BTControlWidget::setConnectEnabled);

    vboxConnections = new QVBoxLayout(this);
    vboxConnections->addWidget(findBtn);
    vboxConnections->addWidget(conBtn);
    vboxConnections->addWidget(dconBtn);
    vboxConnections->addWidget(streamToggleBtn);
}

void BTControlWidget::setConnectEnabled(bool enable)
{
    conBtn->setEnabled(enable);
}

void BTControlWidget::connectRequested()
{
    m_bt->connectModule();
}

void BTControlWidget::disconnectRequested()
{
    m_bt->onDisconnectRequested();
}

void BTControlWidget::streamingToggledRequested()
{
    m_bt->onToggleStreamRequested();
}
