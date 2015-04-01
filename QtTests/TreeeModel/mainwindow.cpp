#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>



class MyObject {
public:
  enum { LIGHT, CAMERA, OBJECT3D };
  MyObject(const std::string& Name)
      : Name(Name), posx(0), posy(0), posz(0) {}

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


  QString val;
     QFile file;
     file.setFileName("../test.json");
     file.open(QIODevice::ReadOnly | QIODevice::Text);
     val = file.readAll();
     file.close();
     qWarning() << val;
     QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
     QJsonObject sett2 = d.object();
     QJsonValue value = sett2.value(QString("appName"));
     qWarning() << value;
     QJsonObject item = value.toObject();
     qWarning() << item["description"];
     qWarning() << item["message"];
     QJsonArray subobj = item["imp"].toArray();
     for(auto e : subobj) {
         qWarning() << e;
         std::cout << "Here" << std::endl;
     }



//     qWarning() << tr("QJsonObject of description: ") << item;

//     /* incase of string value get value and convert into string*/
//     qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
//     QJsonValue subobj = item["description"];
//     qWarning() << subobj.toString();


  model = new QStandardItemModel(this);

  MyObject* CameraObject = new MyObject("Main Camera");
  MyObject* LightObject = new MyObject("Light01");
  MyObject* Cube01Object = new MyObject("Cube01");
  MyObject* Cube02Object = new MyObject("Cube02");

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
