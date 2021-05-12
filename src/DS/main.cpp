#include "DS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DS w;
    w.show();
    return a.exec();
}
