#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Master Raclette (MasterMind remake)");
    w.show();
    return a.exec();
}
