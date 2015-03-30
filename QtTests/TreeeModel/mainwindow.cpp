#include "mainwindow.h"
#include "ui_mainwindow.h"



struct rgOBject {
    std::string name;
    int value1;
    float value2;
};

class rgQObject : public QStandardItem  {
public:
    rgQObject(rgOBject* Object) :QStandardItem(Object->name.c_str()) {

    }
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  model = new QStandardItemModel(this);
  QStandardItem* rootNode = model->invisibleRootItem();
  QStandardItem* cameraItem = new QStandardItem("Main Camera");
  QStandardItem* light01Item = new QStandardItem("Light01");
  QStandardItem* cube01Item = new QStandardItem("Cube01");
  QStandardItem* cube02Item = new QStandardItem("Cube02");
  rootNode->appendRow(cameraItem);
  rootNode->appendRow(light01Item);
  rootNode->appendRow(cube01Item);
  cube01Item->appendRow(cube02Item);


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
    mapper->setRootIndex(index.parent());
    mapper->setCurrentModelIndex(index);
}