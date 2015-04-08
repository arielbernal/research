#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <QWidget>
#include <QDockWidget>
#include <QLineEdit>
#include <toolbox.h>

class ObjectInspector : public QDockWidget {
  Q_OBJECT
public:
  explicit ObjectInspector(const QString &title, QWidget *parent = 0,
                           Qt::WindowFlags flags = 0);
  ~ObjectInspector();

  ToolBox *Properties;
  QLineEdit *ObjectName;
  QLineEdit *PosX;
  QLineEdit *PosY;
  QLineEdit *PosZ;
  QLineEdit *RotX, *RotY, *RotZ;
  QLineEdit *ScaX, *ScaY, *ScaZ;
};

#endif // OBJECTINSPECTOR_H
