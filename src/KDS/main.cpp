#include "KDS.h"
#include <QtWidgets/QApplication>
#include <iostream>

KDS* quoteKDS = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KDS w;
    quoteKDS = &w;
    w.show();

    return a.exec();
}
