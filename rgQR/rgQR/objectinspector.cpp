#include "objectinspector.h"
#include <QDoubleValidator>
#include <QMessageBox>
#include <QScrollArea>
#include <QComboBox>

ObjectInspector::ObjectInspector(const QString& title,
                                 QWidget* parent,
                                 Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags) {

  QVBoxLayout* VLayout = new QVBoxLayout();

  QScrollArea* QA = new QScrollArea();
  Properties = new ToolBox();
  QA->setWidget(Properties);
  QA->setWidgetResizable(true);

  ObjectName = new QLineEdit();
  PosX = new EditDouble(70);
  PosY = new EditDouble(70);
  PosZ = new EditDouble(70);
  RotX = new EditDouble(70);
  RotY = new EditDouble(70);
  RotZ = new EditDouble(70);
  ScaX = new EditDouble(70);
  ScaY = new EditDouble(70);
  ScaZ = new EditDouble(70);

  {
    QVBoxLayout* vbox = new QVBoxLayout();
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Position"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(PosX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(PosY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(PosZ);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Rotation"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(RotX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(RotY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(RotZ);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Scale"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(ScaX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(ScaY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(ScaZ);
      vbox->addItem(hbox);
    }
    QWidget* QW = new QWidget();
    QW->setLayout(vbox);
    Properties->addItem(new ToolItem("Transform", QW));
  }

  // CameraPanel
  {
    CameraPanel = new CameraEditPanel();
    Properties->addItem(new ToolItem("Camera", CameraPanel));
    Properties->hideItem(1);
  }

  {
    LightPanel = new LightEditPanel();
    Properties->addItem(new ToolItem("Light", LightPanel));
    Properties->hideItem(2);
  }
  {
    QWidget* QW = new QWidget();
    Properties->addItem(new ToolItem("Object3D", QW));
    Properties->hideItem(3);
  }

  Tree = new QTreeWidget();
  VLayout->addWidget(Tree);

  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Name:"));
    hbox->addWidget(ObjectName);
    VLayout->addLayout(hbox);
  }

  VLayout->addWidget(QA);
  QWidget* QW = new QWidget();
  QW->setLayout(VLayout);
  setWidget(QW);

  QObject::connect(
      ObjectName, SIGNAL(editingFinished()), this, SLOT(changeName()));
  QObject::connect(PosX, SIGNAL(editingFinished()), this, SLOT(changePosX()));
  QObject::connect(PosY, SIGNAL(editingFinished()), this, SLOT(changePosY()));
  QObject::connect(PosZ, SIGNAL(editingFinished()), this, SLOT(changePosZ()));
  QObject::connect(RotX, SIGNAL(editingFinished()), this, SLOT(changeRotX()));
  QObject::connect(RotY, SIGNAL(editingFinished()), this, SLOT(changeRotY()));
  QObject::connect(RotZ, SIGNAL(editingFinished()), this, SLOT(changeRotZ()));
  QObject::connect(ScaX, SIGNAL(editingFinished()), this, SLOT(changeScaX()));
  QObject::connect(ScaY, SIGNAL(editingFinished()), this, SLOT(changeScaY()));
  QObject::connect(ScaZ, SIGNAL(editingFinished()), this, SLOT(changeScaZ()));

  QObject::connect(
      Tree, SIGNAL(itemSelectionChanged()), this, SLOT(treeItemSelected()));

  Tree->headerItem()->setHidden(true);
}

ObjectInspector::~ObjectInspector() {}

void ObjectInspector::addTreeItems(rg::GLObject* ParentObject,
                                   QTreeWidget* Tree,
                                   QTreeWidgetItem* ParentItem,
                                   int level) {

  for (auto& e : ParentObject->getChildren()) {
    QTreeWidgetItem* child = new QTreeWidgetItem();
    child->setText(0, QString::fromStdString(e.second->getName()));
    if (level == 0)
      Tree->addTopLevelItem(child);
    else {
      ParentItem->addChild(child);
    }
    addTreeItems(e.second, Tree, child, level + 1);
  }
}

void ObjectInspector::setScene(rg::Scene* S) {
  Scene = S;
  CurrentObject = S->getFirstObject();
  rg::GLObject* Root = S->getRoot();
  addTreeItems(Root, Tree, nullptr, 0);
  Tree->expandAll();
}

void ObjectInspector::setCurrentObject(const std::string& Name) {
  CurrentObject = Scene->getObject(Name);
  if (!CurrentObject) {
    return;
    std::cout << "CurrentObject is Empty" << std::endl;
  }
  Properties->hideAll();
  Properties->showItem(0);
  if (CurrentObject->getType() == rg::GLObject::CAMERA) {
    CameraPanel->setCurrentObject(CurrentObject);
    Properties->showItem(1);
  }
  if (CurrentObject->getType() == rg::GLObject::LIGHT) {
    LightPanel->setCurrentObject(CurrentObject);
    Properties->showItem(2);
  }
  if (CurrentObject->getType() == rg::GLObject::OBJECT3D) {
    Properties->showItem(3);
  }

  ObjectName->setText(QString::fromStdString(CurrentObject->getName()));
  PosX->setText(QString::number(CurrentObject->pos.x));
  PosY->setText(QString::number(CurrentObject->pos.y));
  PosZ->setText(QString::number(CurrentObject->pos.z));
  RotX->setText(QString::number(CurrentObject->rot.x));
  RotY->setText(QString::number(CurrentObject->rot.y));
  RotZ->setText(QString::number(CurrentObject->rot.z));
  ScaX->setText(QString::number(CurrentObject->sca.x));
  ScaY->setText(QString::number(CurrentObject->sca.y));
  ScaZ->setText(QString::number(CurrentObject->sca.z));
}

void ObjectInspector::treeItemSelected() {
  QList<QTreeWidgetItem*> Items = Tree->selectedItems();
  if (Items.size() > 0)
    setCurrentObject(Items[0]->text(0).toStdString());
  std::cout << "treeItemSelected" << std::endl;
}

void ObjectInspector::treeItemSelected(QTreeWidgetItem* QItem, int column) {
  setCurrentObject(QItem->text(column).toStdString());
  std::cout << "treeItemSelected" << std::endl;
}

void ObjectInspector::changeName() {
  std::cout << "changeName" << std::endl;
  if (CurrentObject &&
      CurrentObject->getName() != ObjectName->text().toStdString()) {
    QList<QTreeWidgetItem*> Items = Tree->selectedItems();
    if (Items.size() > 0 &&
        Scene->renameObject(CurrentObject->getName(),
                            ObjectName->text().toStdString())) {
      Items[0]->setText(0, ObjectName->text());
    } else {
      ObjectName->blockSignals(true);
      QMessageBox::warning(
          this, "Object Rename Error", "The name already exists");
      ObjectName->blockSignals(false);
    }
  }
}

void ObjectInspector::changePosX() {
  if (CurrentObject)
    CurrentObject->pos.x = PosX->text().toFloat();
}
void ObjectInspector::changePosY() {
  if (CurrentObject)
    CurrentObject->pos.y = PosY->text().toFloat();
}
void ObjectInspector::changePosZ() {
  if (CurrentObject)
    CurrentObject->pos.z = PosZ->text().toFloat();
}

void ObjectInspector::changeRotX() {
  if (CurrentObject)
    CurrentObject->rot.x = RotX->text().toFloat();
}
void ObjectInspector::changeRotY() {
  if (CurrentObject)
    CurrentObject->rot.y = RotY->text().toFloat();
}
void ObjectInspector::changeRotZ() {
  if (CurrentObject)
    CurrentObject->rot.z = RotZ->text().toFloat();
}

void ObjectInspector::changeScaX() {
  if (CurrentObject)
    CurrentObject->sca.x = ScaX->text().toFloat();
}
void ObjectInspector::changeScaY() {
  if (CurrentObject)
    CurrentObject->sca.y = ScaY->text().toFloat();
}
void ObjectInspector::changeScaZ() {
  if (CurrentObject)
    CurrentObject->sca.z = ScaZ->text().toFloat();
}
