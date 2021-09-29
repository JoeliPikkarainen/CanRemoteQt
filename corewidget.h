#ifndef COREWIDGET_H
#define COREWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>

//Widgets

#include "src/graphics/logterminal.h"
#include "src/graphics/btcontrolwidget.h"
#include "src/bt_com_if.h"
#include "src/graphics/qvboxaswidget.h"
#include "src/graphics/modulecontrolwidget.h"
#include "src/moduleapi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CoreWidget; }
QT_END_NAMESPACE

class CoreWidget : public QWidget
{
    Q_OBJECT

public:
    CoreWidget(QWidget *parent = nullptr);
    ~CoreWidget();

    static void slog(QString str);

    BT_COM_IF* bt();

signals:
    void term_log(QString str);

private:
    Ui::CoreWidget *ui;

    BT_COM_IF* m_bt;
    ModuleApi* m_api;

    BTControlWidget* m_bt_widget;
    LogTerminal* m_logger;
    ModuleControlWidget* m_ctrl_widget;

    QTabWidget* mainTabs;
    QVBoxAsWidget* mainVLayout;
};
#endif // COREWIDGET_H
