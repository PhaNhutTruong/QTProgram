#include "mainwindow.h"
#include "flogin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FLogin w;
    w.show();
    return a.exec();
}
