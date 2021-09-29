#include "qvboxaswidget.h"

QVBoxAsWidget::QVBoxAsWidget(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout(this);
}

void QVBoxAsWidget::addWidget(QWidget *w)
{
    vbox->addWidget(w);
}
