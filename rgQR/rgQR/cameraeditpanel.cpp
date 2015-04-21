#include <cameraeditpanel.h>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <qformline.h>
#include <gl/rgglcamera.h>

CameraEditPanel::CameraEditPanel()
    : fov(new EditDouble(100)),
      near(new EditDouble(100)),
      far(new EditDouble(100)),
      view_x(new EditDouble(100)),
      view_y(new EditDouble(100)),
      view_w(new EditDouble(100)),
      view_h(new EditDouble(100)) {

  QVBoxLayout* vbox = new QVBoxLayout();
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Projection"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    projection = new QComboBox();
    projection->addItem("Orthographic");
    projection->addItem("Perspective");
    hbox->addWidget(projection);
    vbox->addItem(hbox);
    vbox->addWidget(new QFormLine());
  }
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Field of View"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    hbox->addWidget(fov);
    vbox->addItem(hbox);
    vbox->addWidget(new QFormLine());
  }
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
    vbox->addWidget(new QFormLine());
  }
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
  setLayout(vbox);

  QObject::connect(projection,
                   SIGNAL(currentIndexChanged(int)),
                   this,
                   SLOT(changeProjection(int)));
  QObject::connect(fov, SIGNAL(editingFinished()), this, SLOT(changeFov()));
  QObject::connect(far, SIGNAL(editingFinished()), this, SLOT(changeFar()));
  QObject::connect(near, SIGNAL(editingFinished()), this, SLOT(changeNear()));
  QObject::connect(
      view_x, SIGNAL(editingFinished()), this, SLOT(changeViewX()));
  QObject::connect(
      view_y, SIGNAL(editingFinished()), this, SLOT(changeViewY()));
  QObject::connect(
      view_w, SIGNAL(editingFinished()), this, SLOT(changeViewW()));
  QObject::connect(
      view_h, SIGNAL(editingFinished()), this, SLOT(changeViewH()));
}

void CameraEditPanel::setCurrentObject(rg::GLObject* O) {
  CurrentObject = static_cast<rg::GLCamera*>(O);
  projection->setCurrentIndex(CurrentObject->projection);
  fov->setText(QString::number(CurrentObject->fov));
  near->setText(QString::number(CurrentObject->near));
  far->setText(QString::number(CurrentObject->far));
  view_x->setText(QString::number(CurrentObject->view_x));
  view_y->setText(QString::number(CurrentObject->view_y));
  view_w->setText(QString::number(CurrentObject->view_w));
  view_h->setText(QString::number(CurrentObject->view_h));
}

void CameraEditPanel::changeProjection(int index) {
  if (CurrentObject)
    CurrentObject->projection = index;
}

void CameraEditPanel::changeFov() {
  if (CurrentObject)
    CurrentObject->fov = fov->text().toFloat();
}

void CameraEditPanel::changeNear() {
  if (CurrentObject)
    CurrentObject->near = near->text().toFloat();
}

void CameraEditPanel::changeFar() {
  if (CurrentObject)
    CurrentObject->far = far->text().toFloat();
}

void CameraEditPanel::changeViewX() {
  if (CurrentObject)
    CurrentObject->view_x = view_x->text().toFloat();
}

void CameraEditPanel::changeViewY() {
  if (CurrentObject)
    CurrentObject->view_y = view_y->text().toFloat();
}

void CameraEditPanel::changeViewW() {
  if (CurrentObject)
    CurrentObject->view_w = view_w->text().toFloat();
}

void CameraEditPanel::changeViewH() {
  if (CurrentObject)
    CurrentObject->view_h = view_h->text().toFloat();
}
