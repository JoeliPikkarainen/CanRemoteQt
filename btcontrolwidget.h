#ifndef BTCONTROLWIDGET_H
#define BTCONTROLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QPushButton>

class BTControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BTControlWidget(QWidget *parent = nullptr);

public slots:
    void setConnectEnabled(bool enable);

signals:
    void connectRequested();

private:
    QPushButton* conBtn;
    QPushButton* findBtn;

};

#endif // BTCONTROLWIDGET_H
