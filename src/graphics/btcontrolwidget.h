#ifndef BTCONTROLWIDGET_H
#define BTCONTROLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QPushButton>
#include <QVBoxLayout>

class BTControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BTControlWidget(QWidget *parent = nullptr);

public slots:
    void setConnectEnabled(bool enable);

signals:
    void connectRequested();
    void disconnectRequested();

private:

    QVBoxLayout* vboxConnections;
    QPushButton* conBtn;
    QPushButton* findBtn;
    QPushButton* dconBtn;

};

#endif // BTCONTROLWIDGET_H
