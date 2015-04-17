#ifndef CAMERAEDITPANEL_H
#define CAMERAEDITPANEL_H

#include <vallineedit.h>
#include <QComboBox>
#include <gl/rgglcamera.h>

class CameraEditPanel : public QWidget {
    Q_OBJECT
 public:
  CameraEditPanel();

  void setCurrentObject(rg::GLObject* O);

 public slots:
  void changeFov();

 private:
  rg::GLCamera* CurrentObject;

  size_t projection;
  EditDouble* fov;
  EditDouble* near;
  EditDouble* far;
  EditDouble* view_x;
  EditDouble* view_y;
  EditDouble* view_w;
  EditDouble* view_h;


};

#endif  // CAMERAEDITPANEL_H
