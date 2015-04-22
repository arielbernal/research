#ifndef LIGHTEDITPANEL
#define LIGHTEDITPANEL

#include <vallineedit.h>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <gl/rggllight.h>

class LightEditPanel : public QWidget {
  Q_OBJECT
 public:
  LightEditPanel();

  void setCurrentObject(rg::GLObject* O);

 public slots:
  void pickLaColor();
  void pickLdColor();
  void pickLsColor();
  void changeLightType(int index);
  void changeAa();
  void changeAb();
  void changeAc();

  void changeSpotAngle();
  void changeSpotCosCutoff();
  void changeSpotExponent();

 protected:
  glm::vec3 convertQColorToVec3(QColor color);
  QColor convertVec3ToQColor(glm::vec3& vec);
  void setButtonBackgroundColor(QPushButton* button, glm::vec3& color);

 private:
  rg::GLLight* CurrentObject;

  QComboBox* light_type;
  QPushButton* la;  // ambient light
  QPushButton* ld;  // difuse light
  QPushButton* ls;  // specular light
  // Point Light Only
  EditDouble* Ac;  // Constant Attenuation
  EditDouble* Ab;  // Linear Attenuation
  EditDouble* Aa;  // Quadratic Attenuation
  // Spot light only
  EditDouble* SpotAngle;
  EditDouble* SpotCosCutoff;
  EditDouble* SpotExponent;



  QWidget* SpotGroup;
  QWidget* PointGroup;
};

#endif  // LIGHTEDITPANEL
