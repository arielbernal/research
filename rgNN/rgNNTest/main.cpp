#include "mainwindow.h"
#include <QApplication>



int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
        MainWindow w;
        w.setGeometry(2400, 100, 800, 800);
        w.show();
    return a.exec();
}
