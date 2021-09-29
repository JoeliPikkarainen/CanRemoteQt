#include "modulecontrolwidget.h"
#include "framebuilder.h"


ModuleControlWidget::ModuleControlWidget(BT_COM_IF* bt, ModuleApi *api, QWidget *parent) : QWidget(parent), m_bt(bt), m_api(api)
{
    mainVLine = new QVBoxLayout(this);

    //CAN RATE CONTROL PART:
    canRateControlLine = new QHBoxLayout(this);
    canRateLabel = new QLabel(this);
    canRateLabel->setText("CAN BAUD (kbs)");
    canRateControlLine->addWidget(canRateLabel);

    canRateGetBtn = new QPushButton(this);
    canRateGetBtn->setText("GET");
    canRateControlLine->addWidget(canRateGetBtn);

    canRateSetBtn = new QPushButton(this);
    canRateSetBtn->setText("SET");
    canRateControlLine->addWidget(canRateSetBtn);

    canRateLineEdit = new QLineEdit(this);
    canRateLineEdit->setText("0");
    canRateLineEdit->setMaximumWidth(100);
    canRateControlLine->addWidget(canRateLineEdit);

    cabRateQLabel = new QLabel(this);
    cabRateQLabel->setText("<NO-DATA>");
    cabRateQLabel->setMaximumWidth(100);
    canRateControlLine->addWidget(cabRateQLabel);

    connect(m_api,&ModuleApi::frame_received_CANRATE, this, &ModuleControlWidget::onCanRateReceived);

    mainVLine->addLayout(canRateControlLine);

    connect(canRateGetBtn,&QPushButton::clicked, this, &ModuleControlWidget::request_get_canrate);
    connect(canRateSetBtn,&QPushButton::clicked, this, &ModuleControlWidget::request_set_canrate);

}

void ModuleControlWidget::onCanRateReceived(COM_FRAME rxframe)
{
    union{
        uint16_t u16;
        uint8_t u8[2];
    }un8t16;

    un8t16.u8[1] = rxframe.m_data_buff[1];
    un8t16.u8[0] = rxframe.m_data_buff[0];

    QString str = QString("%1").arg(un8t16.u16);
    cabRateQLabel->setText(str);

}

void ModuleControlWidget::request_get_canrate()
{
    COM_FRAME request = FrameBuilder::mkframe_Get_can_rate();
    m_bt->transmitFrame(request);
}

void ModuleControlWidget::request_set_canrate()
{
    uint16_t rate;
    QString str = canRateLineEdit->text();
    rate = str.toUInt();

    COM_FRAME txframe = FrameBuilder::mkframe_Set_can_rate(rate);

    m_api->transmitFrame(txframe);

}
