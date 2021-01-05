#include "mainwindow.h"
#include "rand.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Rand::init();

    MainWindow w;
    w.openMainMenu();
    w.show();

    return a.exec();
}
