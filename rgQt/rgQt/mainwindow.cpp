#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <io/jsoncons/json.hpp>

#define GLEW_STATIC
//#include <GL/glew.h>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QWindow>

MainWindow::MainWindow(rg::GLScene& S, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), Scene(S) {
  ui->setupUi(this);
  std::cout << ui->glScene->isInitialized() << std::endl;
  //    Scene.loadFromJsonFile("");
  //    Scene.dumpTree();
}

MainWindow::~MainWindow() { delete ui; }
