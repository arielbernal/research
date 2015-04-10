#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <objectinspector.h>
#include <QLabel>
#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  objectInspector = new ObjectInspector("Hierarchy", this);
  ui->setupUi(this);
  addDockWidget(Qt::LeftDockWidgetArea, objectInspector);
  Scene = new rg::Scene();
  Scene->addCamera("Main Camera");
  Scene->addLight("Light01");
  Scene->addObject3D("Cube01", rg::GLObject3D::CUBOID);
  objectInspector->setScene(Scene);
}

MainWindow::~MainWindow() { delete ui; }
