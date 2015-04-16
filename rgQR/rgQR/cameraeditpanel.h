#ifndef CAMERAEDITPANEL_H
#define CAMERAEDITPANEL_H

#include <vallineedit.h>
#include <QComboBox>

struct CameraEditPanel {
  CameraEditPanel()
      : fov(new EditDouble(100)),
        near(new EditDouble(100)),
        far(new EditDouble(100)),
        view_x(new EditDouble(100)),
        view_y(new EditDouble(100)),
        view_w(new EditDouble(100)),
        view_h(new EditDouble(100)) {
    create();
  }
  size_t projection;
  EditDouble* fov;
  EditDouble* near;
  EditDouble* far;
  EditDouble* view_x;
  EditDouble* view_y;
  EditDouble* view_w;
  EditDouble* view_h;

  void create() {
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* vbox = new QVBoxLayout();
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Projection"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      QComboBox* QB = new QComboBox();
      QB->addItem("Orthographic");
      QB->addItem("Perspective");
      hbox->addWidget(QB);
      vbox->addItem(hbox);
    }
    vbox->addWidget(line);
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Field of View"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addWidget(fov);
      vbox->addItem(hbox);
    }
    vbox->addWidget(line);
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Clipping Planes"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addSpacerItem(
          new QSpacerItem(2, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
      {
        QVBoxLayout* vbox1 = new QVBoxLayout();
        {
          QHBoxLayout* hbox1 = new QHBoxLayout();
          hbox1->addWidget(new QLabel("Near "));
          hbox1->addWidget(near);
          vbox1->addItem(hbox1);
        }
        vbox1->addSpacerItem(new QSpacerItem(
            1, 5, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
        {
          QHBoxLayout* hbox1 = new QHBoxLayout();
          hbox1->addWidget(new QLabel("Far"));
          hbox1->addWidget(far);
          vbox1->addItem(hbox1);
        }
        hbox->addItem(vbox1);
      }
      vbox->addItem(hbox);
    }
    vbox->addWidget(line);
    {
      QHBoxLayout* hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Viewport"));
      hbox->addSpacerItem(new QSpacerItem(
          20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
      hbox->addSpacerItem(
          new QSpacerItem(2, 1, QSizePolicy::Fixed, QSizePolicy::Fixed));
      {
        QVBoxLayout* vbox1 = new QVBoxLayout();
        {
          QHBoxLayout* hbox1 = new QHBoxLayout();
          hbox1->addWidget(new QLabel("X "));
          hbox1->addWidget(view_x);
          hbox1->addWidget(new QLabel(" Y"));
          hbox1->addWidget(view_y);
          vbox1->addItem(hbox1);
        }
        vbox1->addSpacerItem(new QSpacerItem(
            1, 5, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
        {
          QHBoxLayout* hbox1 = new QHBoxLayout();
          hbox1->addWidget(new QLabel("W"));
          hbox1->addWidget(view_w);
          hbox1->addWidget(new QLabel("H"));
          hbox1->addWidget(view_h);
          vbox1->addItem(hbox1);
        }
        hbox->addItem(vbox1);
      }
      vbox->addItem(hbox);
    }
    Widget = new QWidget();
    Widget->setLayout(vbox);
  }

  QWidget* Widget;
};

#endif  // CAMERAEDITPANEL_H
