#include "capturemotion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CaptureMotion w;
    w.show();

    return a.exec();
}
