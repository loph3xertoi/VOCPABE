#include "ES.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ES w;
    w.show();
    return a.exec();
}
