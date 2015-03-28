#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <io/jsoncons/json.hpp>
#include <gl/rgGLObject.h>

MainWindow::MainWindow(rg::GLScene& S, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), Scene(S) {
  ui->setupUi(this);

  connect(
      ui->glScene, SIGNAL(initialized()), this, SLOT(GLWidgetInitialized()));

  ui->treeWidget->setAcceptDrops(true);
  ui->treeWidget->setDragEnabled(true);
  ui->treeWidget->setDropIndicatorShown(true);
  ui->treeWidget->viewport()->setAcceptDrops(true);
  ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::buildTree(QTreeWidget* tree,
                           QTreeWidgetItem* item,
                           rg::GLObject* Node) {
  for (auto& e : Node->getChildren()) {
    QTreeWidgetItem* it;
    if (item == 0) {
      it = new QTreeWidgetItem(
          tree, QStringList(QObject::tr(e.second->getName().c_str())));
      it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
    } else {
      it = new QTreeWidgetItem(
          QStringList(QObject::tr(e.second->getName().c_str())));
      it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);
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
  QTreeWidgetItem* root = ui->treeWidget->invisibleRootItem();
  root->setFlags(root->flags() | Qt::ItemIsDropEnabled);
  buildTree(ui->treeWidget, nullptr, Scene.getRootNode());
}

void MainWindow::on_actionExit_triggered() {
  close();
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
  //  ui->labelName->setText(item->text(column));
}
