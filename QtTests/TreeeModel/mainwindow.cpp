#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

class MyObject {
public:
  MyObject(const std::string& Name, int posx, int posy, int posz)
      : Name(Name), posx(posx), posy(posy), posz(posz) {}

  std::string getName() { return Name; }
  void setName(const std::string& name) { Name = name; }

  int getPosx() { return posx; }
  void setPosx(int x) { posx = x; }
  int getPosy() { return posy; }
  void setPosy(int y) { posy = y; }
  int getPosz() { return posz; }
  void setPosz(int z) { posz = z; }

private:
  std::string Name;
  int posx;
  int posy;
  int posz;
};

class QtMyObject : public QStandardItem {
public:
  QtMyObject(MyObject* Object)
      : QStandardItem(QString::fromStdString(Object->getName())),
        Object(Object) {
    List.append(this);
    List.append(new QStandardItem(QString::number(Object->getPosx())));
    List.append(new QStandardItem(QString::number(Object->getPosy())));
    List.append(new QStandardItem(QString::number(Object->getPosz())));
  }

  QList<QStandardItem*>& getList() { return List; }
  QStandardItem* getItem() {
    if (!List.empty())
      return List[0];
    return NULL;
  }
  void appendRow(QtMyObject* qtMy) {
    static_cast<QStandardItem*>(this)->appendRow(qtMy->getList());
  }
  MyObject* getObject() { return Object; }

private:
  MyObject* Object;
  QList<QStandardItem*> List;
};


QtMyObject* currentItem;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  model = new QStandardItemModel(this);

  MyObject* CameraObject = new MyObject("Main Camera", 100, 101, 102);
  MyObject* LightObject = new MyObject("Light01", 200, 201, 202);
  MyObject* Cube01Object = new MyObject("Cube01", 300, 301, 302);
  MyObject* Cube02Object = new MyObject("Cube02", 400, 401, 402);

  QtMyObject* rootNode = static_cast<QtMyObject*>(model->invisibleRootItem());
  QtMyObject* CameraQtObject = new QtMyObject(CameraObject);
  QtMyObject* LightQtObject = new QtMyObject(LightObject);
  QtMyObject* Cube01QtObject = new QtMyObject(Cube01Object);
  QtMyObject* Cube02QtObject = new QtMyObject(Cube02Object);
  rootNode->appendRow(CameraQtObject);
  rootNode->appendRow(LightQtObject);
  rootNode->appendRow(Cube01QtObject);
  Cube01QtObject->appendRow(Cube02QtObject);

  ui->treeView->setModel(model);
  ui->treeView->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                QAbstractItemView::DoubleClicked);
  ui->treeView->hideColumn(1);
  ui->treeView->hideColumn(2);
  ui->treeView->hideColumn(3);

  mapper = new QDataWidgetMapper(this);
  mapper->setModel(model);
  mapper->addMapping(ui->editName, 0);
  mapper->addMapping(ui->editPosX, 1);
  mapper->addMapping(ui->editPosY, 2);
  mapper->addMapping(ui->editPosZ, 3);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_treeView_clicked(const QModelIndex& index) {
  mapper->setRootIndex(index.parent());
  mapper->setCurrentModelIndex(index);
  currentItem = static_cast<QtMyObject*>(model->itemFromIndex(index));
}

void MainWindow::on_editPosX_editingFinished() {
  MyObject* obj = currentItem->getObject();
  obj->setPosx(ui->editPosX->text().toInt());
  std::cout << "Here we got the current object:"
              << currentItem->getObject()->getPosx() << std::endl;
}
