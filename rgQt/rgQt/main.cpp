#include "mainwindow.h"
#include <QApplication>
#include <gl/rgGLScene.h>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  rg::GLScene Scene;
  MainWindow w(Scene);
  w.show();



  return a.exec();
}
