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
  Scene->addLight("Light02");
  Scene->addCamera("Second Camera");
  Scene->addObject3D("Cube01", rg::GLObject3D::CUBOID);
  Scene->addObject3D("Cube02", rg::GLObject3D::CUBOID, "Cube01");
  objectInspector->setScene(Scene);

  connect(
      ui->glScene, SIGNAL(initialized()), this, SLOT(GLWidgetInitialized()));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(GLDrawScene()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::GLWidgetInitialized() {
  std::cout << "GLWidget Initialized!" << std::endl;
}


void MainWindow::GLDrawScene() {
    std::cout << "pushed" << std::endl;

    ui->glScene->update();
}
