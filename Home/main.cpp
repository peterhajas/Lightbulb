#include <QtGui/QApplication>
#include "homedisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeDisplay w;
    w.show();
    return a.exec();
}
