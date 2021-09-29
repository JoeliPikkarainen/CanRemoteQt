#include "corewidget.h"
#include "ui_corewidget.h"

#include "src/bt_com_if.h"

#include <QApplication>
#include <QRect>
#include <QDesktopWidget>
#include <QScreen>

CoreWidget::CoreWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CoreWidget)
{
    ui->setupUi(this);

#ifdef ANDROID_BUILD
     QRect rec = QApplication::screens().first()->geometry();
     int height = rec.height();
     int width = rec.width();
     this->setFixedSize(width,height - 100);
#endif

#ifdef DESKTOP_BUILD
     QRect rec = QApplication::screens().first()->geometry();
     int height = rec.height();
     int width = rec.width();
     this->resize(width / 3 ,height - 100);
#endif

    mainTabs = new QTabWidget(this);
    mainVLayout = new QVBoxAsWidget(this);

    m_bt = new BT_COM_IF(this);
    m_api = new ModuleApi(m_bt,this);
    m_api->start();

    m_logger = new LogTerminal(this);

    m_bt_widget = new BTControlWidget(this, m_bt);

    m_ctrl_widget = new ModuleControlWidget(m_bt,m_api,this);

    mainVLayout->addWidget(m_bt_widget);
    mainVLayout->addWidget(m_logger);

    mainTabs->setGeometry(0,0,this->width(),this->height());
    mainTabs->addTab((QWidget*)mainVLayout,"CONNECT");

    mainTabs->addTab(m_ctrl_widget,"CONTROL");

    connect(m_bt,&BT_COM_IF::canModuleFound, m_logger,&LogTerminal::append);
    connect(m_bt,&BT_COM_IF::log, m_logger, &LogTerminal::append);

    connect(this,&CoreWidget::term_log, m_logger, &LogTerminal::append);
}

CoreWidget::~CoreWidget()
{
    delete ui;
}

BT_COM_IF* CoreWidget::bt()
{
    return m_bt;
}


