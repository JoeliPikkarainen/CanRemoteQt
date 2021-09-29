#ifndef QVBOXASWIDGET_H
#define QVBOXASWIDGET_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>

//Use this as a QWidget class with the QVboxLayout
class QVBoxAsWidget : public QWidget
{
    Q_OBJECT
    using QWidget::setGeometry;
public:
    explicit QVBoxAsWidget(QWidget *parent = nullptr);
    void addWidget(QWidget* w);

signals:

private:
    QVBoxLayout* vbox;

};

#endif // QVBOXASWIDGET_H
