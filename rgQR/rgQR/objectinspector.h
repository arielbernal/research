#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <QWidget>
#include <QDockWidget>
#include <QLineEdit>
#include <toolbox.h>
#include <vallineedit.h>
#include <scene.h>
#include <QTreeWidget>

class ObjectInspector : public QDockWidget {
  Q_OBJECT
 public:
  explicit ObjectInspector(const QString& title,
                           QWidget* parent = 0,
                           Qt::WindowFlags flags = 0);
  ~ObjectInspector();

  void setScene(rg::Scene* S);
  void addTreeItems(rg::GLObject* ParentObject, QTreeWidget* Tree, QTreeWidgetItem* ParentItem, int level);


  void setCurrentObject(const std::string& Name);

  rg::Scene* Scene;
  rg::GLObject* CurrentObject;

  QTreeWidget *Tree;
  ToolBox* Properties;

  // ObjectName
  QLineEdit* ObjectName;
  // Transform
  EditDouble* PosX, *PosY, *PosZ;
  EditDouble* RotX, *RotY, *RotZ;
  EditDouble* ScaX, *ScaY, *ScaZ;




 public slots:
  void changeName();
  void changePosX();
  void changePosY();
  void changePosZ();
  void changeRotX();
  void changeRotY();
  void changeRotZ();
  void changeScaX();
  void changeScaY();
  void changeScaZ();
  void treeItemSelected(QTreeWidgetItem* QItem,int column);
  void treeItemSelected();
};

#endif  // OBJECTINSPECTOR_H
