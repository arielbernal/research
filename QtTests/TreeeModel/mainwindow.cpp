#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  model = new QStandardItemModel(this);
  QStandardItem* rootNode = model->invisibleRootItem();
  QList<QStandardItem*> cameraItem;
  cameraItem.append(new QStandardItem("Main Camera"));
  cameraItem.append(new QStandardItem("10"));
  cameraItem.append(new QStandardItem("20"));
  cameraItem.append(new QStandardItem("30"));

  QStandardItem* light01Item = new QStandardItem("Light01");
  QStandardItem* cube01Item = new QStandardItem("Cube01");
  QList<QStandardItem*> cube02Item;
  cube02Item.append(new QStandardItem("Cube02"));
  cube02Item.append(new QStandardItem("200"));
  cube02Item.append(new QStandardItem("350"));
  cube02Item.append(new QStandardItem("380"));

  rootNode->appendRow(cameraItem);
  rootNode->appendRow(light01Item);
  rootNode->appendRow(cube01Item);
  cube01Item->appendRow(cube02Item);


  ui->treeView->setModel(model);
  ui->treeView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

  mapper = new QDataWidgetMapper();
  mapper->setModel(model);
  mapper->addMapping(ui->editName, 0);
  mapper->addMapping(ui->editPosX, 1);
  mapper->addMapping(ui->editPosY, 2);
  mapper->addMapping(ui->editPosZ, 3);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    mapper->setRootIndex(index.parent());
    mapper->setCurrentModelIndex(index);
}
