#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  model = new QStringListModel(this);
  QStringList list;
  list << "cats" << "dogs" << "birds";
  model->setStringList(list);
  ui->treeView->setModel(model);
  ui->treeView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

  mapper = new QDataWidgetMapper();
  mapper->setModel(model);
  mapper->addMapping(ui->lineEdit, 0);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    mapper->setCurrentModelIndex(index);
}
