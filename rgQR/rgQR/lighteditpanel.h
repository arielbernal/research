#ifndef LIGHTEDITPANEL
#define LIGHTEDITPANEL

#include <vallineedit.h>
#include <QComboBox>
#include <QPushButton>
#include <gl/rggllight.h>

class LightEditPanel : public QWidget {
  Q_OBJECT
 public:
  LightEditPanel();

  void setCurrentObject(rg::GLObject* O);

 public slots:
  void pickLaColor();

 protected:
  glm::vec3 convertQColorToVec3(QColor color);
  QColor convertVec3ToQColor(glm::vec3& vec);
  void setButtonBackgroundColor(QPushButton* button, glm::vec3& color);

 private:
  rg::GLLight* CurrentObject;

  QComboBox* light_type;
  QPushButton* la;  // ambient light
};

#endif  // LIGHTEDITPANEL
