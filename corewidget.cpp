#include "corewidget.h"
#include "ui_corewidget.h"
#include "bt_com_if.h"


CoreWidget::CoreWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoreWidget)
{
    ui->setupUi(this);
    m_bt = new BT_COM_IF(this);
    m_logger = new LogTerminal(this);
    mainVLayout = new QVBoxLayout(this);
    m_bt_widget = new BTControlWidget(this);

    mainVLayout->addWidget(m_bt_widget);
    mainVLayout->addWidget(m_logger);

    connect(m_bt,&BT_COM_IF::canModuleFound, m_logger,&LogTerminal::append);
    connect(m_bt,&BT_COM_IF::moduleAvailable,m_bt_widget, &BTControlWidget::setConnectEnabled);
    connect(m_bt,&BT_COM_IF::log, m_logger, &LogTerminal::append);

    connect(m_bt_widget, &BTControlWidget::connectRequested, m_bt, &BT_COM_IF::connectModule);

}

CoreWidget::~CoreWidget()
{
    delete ui;
}

