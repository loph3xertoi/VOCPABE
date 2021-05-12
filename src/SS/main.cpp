#include "SS.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SS w;
    w.show();
    return a.exec();
}
