#ifndef CAMERAEDITPANEL_H
#define CAMERAEDITPANEL_H


#include <vallineedit.h>


struct CameraEditPanel {
  CameraEditPanel(int width)
      : fov(new EditDouble(width)),
        near(new EditDouble(width)),
        far(new EditDouble(width)),
        view_x(new EditDouble(width)),
        view_y(new EditDouble(width)),
        view_w(new EditDouble(width)),
        view_h(new EditDouble(width)) {}
  size_t projection;
  EditDouble* fov;
  EditDouble* near;
  EditDouble* far;
  EditDouble* view_x;
  EditDouble* view_y;
  EditDouble* view_w;
  EditDouble* view_h;
};

#endif // CAMERAEDITPANEL_H

