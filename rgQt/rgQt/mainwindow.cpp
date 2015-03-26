#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QWindow>

#include <io/jsoncons/json.hpp>
#include <gl/rgGLObject.h>

MainWindow::MainWindow(rg::GLScene& S, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), Scene(S) {
  ui->setupUi(this);

  connect(ui->glScene, SIGNAL(initialized()), this,
          SLOT(GLWidgetInitialized()));
}

void MainWindow::buildTree(QTreeWidget* tree, QTreeWidgetItem* item,
                           rg::GLObject* Node) {
  for (auto e : Node->getChildren()) {
    QTreeWidgetItem* it;
    if (item == 0) {
      it = new QTreeWidgetItem(
          tree, QStringList(QObject::tr(e.second->getName().c_str())));
      it->setFlags(it->flags() | Qt::ItemIsEditable);
    } else {
      it = new QTreeWidgetItem(
          QStringList(QObject::tr(e.second->getName().c_str())));
      it->setFlags(it->flags() | Qt::ItemIsEditable);
      item->addChild(it);
    }
    buildTree(tree, it, e.second);
  }
}

void MainWindow::GLWidgetInitialized() {
  std::cout << "GLWidget Initialized!" << std::endl;
  Scene.loadFromJsonFile("../scene1.json");
  Scene.dumpTree();
  ui->treeWidget->clear();
  ui->treeWidget->setColumnCount(1);
  ui->treeWidget->header()->hide();
  buildTree(ui->treeWidget, nullptr, Scene.getRootNode());
}

MainWindow::~MainWindow() { delete ui; }
