#ifndef COREWIDGET_H
#define COREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

//Widgets
#include <logterminal.h>
#include <btcontrolwidget.h>

class BT_COM_IF;
QT_BEGIN_NAMESPACE
namespace Ui { class CoreWidget; }
QT_END_NAMESPACE

class CoreWidget : public QWidget
{
    Q_OBJECT

public:
    CoreWidget(QWidget *parent = nullptr);
    ~CoreWidget();

private:
    Ui::CoreWidget *ui;

    BT_COM_IF* m_bt;
    LogTerminal* m_logger;
    BTControlWidget* m_bt_widget;

    QVBoxLayout* mainVLayout;
};
#endif // COREWIDGET_H
