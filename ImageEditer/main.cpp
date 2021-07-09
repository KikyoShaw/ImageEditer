#include "ImageEditer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageEditer w;
    w.show();
    return a.exec();
}
