#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <QWidget>
#include <QDockWidget>
#include <QLineEdit>
#include <toolbox.h>
#include <vallineedit.h>

class ObjectInspector : public QDockWidget {
  Q_OBJECT
public:
  explicit ObjectInspector(const QString &title, QWidget *parent = 0,
                           Qt::WindowFlags flags = 0);
  ~ObjectInspector();

  void SetObjectValues();

  ToolBox *Properties;

  // ObjectName
  QLineEdit *ObjectName;
  // Transform
  ValLineEdit *PosX, *PosY, *PosZ;
  ValLineEdit *RotX, *RotY, *RotZ;
  ValLineEdit *ScaX, *ScaY, *ScaZ;
};

#endif // OBJECTINSPECTOR_H
