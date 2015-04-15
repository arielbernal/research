#ifndef CAMERAEDITPANEL_H
#define CAMERAEDITPANEL_H

#include <vallineedit.h>
#include <QComboBox>

struct CameraEditPanel {
  CameraEditPanel(int width)
      : fov(new EditDouble(width)), near(new EditDouble(width)),
        far(new EditDouble(width)), view_x(new EditDouble(width)),
        view_y(new EditDouble(width)), view_w(new EditDouble(width)),
        view_h(new EditDouble(width)) {
    create();
  }
  size_t projection;
  EditDouble *fov;
  EditDouble *near;
  EditDouble *far;
  EditDouble *view_x;
  EditDouble *view_y;
  EditDouble *view_w;
  EditDouble *view_h;

  void create() {
    QVBoxLayout *vbox = new QVBoxLayout();
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Projection"));
      QSpacerItem *item = new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      QComboBox *QB = new QComboBox();
      QB->addItem("Orthographic");
      QB->addItem("Perspective");
      hbox->addWidget(QB);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Field of View"));
      QSpacerItem *item = new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      hbox->addWidget(fov);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Viewport"));
      QSpacerItem *item = new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      QVBoxLayout *vbox1 = new QVBoxLayout();
      {
        QHBoxLayout *hbox = new QHBoxLayout();
        hbox->addWidget(new QLabel("Rotation"));
        QSpacerItem *item = new QSpacerItem(
            20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        hbox->addSpacerItem(item);
        hbox->addWidget(new QLabel("X"));
        hbox->addWidget(view_x);
        hbox->addWidget(new QLabel(" Y"));
        hbox->addWidget(view_y);
        vbox1->addItem(hbox);
      }
      {
        QHBoxLayout *hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("W"));
        hbox1->addWidget(view_w);
        hbox1->addWidget(new QLabel("H"));
        hbox1->addWidget(view_h);
        vbox1->addItem(hbox1);
      }
      hbox->addItem(vbox1);
      vbox->addItem(hbox);
    }
    Widget = new QWidget();
    Widget->setLayout(vbox);
  }

  QWidget *Widget;
};

#endif // CAMERAEDITPANEL_H
