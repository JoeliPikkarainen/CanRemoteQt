#include "corewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoreWidget w;
    w.show();
    return a.exec();
}
