#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Connect Slot to execute Exit Code
    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(on_ApplicationExit()));

    return a.exec();
}

