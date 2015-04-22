#include <lighteditpanel.h>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <qformline.h>
#include <QDebug>
#include <QStackedWidget>

#include <gl/rgglcamera.h>
#include <vallineedit.h>

LightEditPanel::LightEditPanel()
    : light_type(new QComboBox),
      la(new QPushButton()),
      ld(new QPushButton()),
      ls(new QPushButton()),
      Ac(new EditDouble(70)),
      Ab(new EditDouble(70)),
      Aa(new EditDouble(70)),
      SpotAngle(new EditDouble(70)),
      SpotCosCutoff(new EditDouble(70)),
      SpotExponent(new EditDouble(70)) {

  la->setStyleSheet("QPushButton { border: 1px solid #000000;}");
  la->setFlat(true);
  la->setFixedWidth(200);
  ld->setStyleSheet("QPushButton { border: 1px solid #000000;}");
  ld->setFlat(true);
  ld->setFixedWidth(200);
  ls->setStyleSheet("QPushButton { border: 1px solid #000000;}");
  ls->setFlat(true);
  ls->setFixedWidth(200);

  QVBoxLayout* vbox = new QVBoxLayout();
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Type"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    light_type->addItem("Directional");
    light_type->addItem("Point");
    light_type->addItem("Spot");
    light_type->addItem("Area");
    hbox->addWidget(light_type);
    vbox->addItem(hbox);
  }
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Attenuation"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    {
      QVBoxLayout* vbox1 = new QVBoxLayout();
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Constant "));
        hbox1->addWidget(Ac);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Linear "));
        hbox1->addWidget(Ab);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Quadratic "));
        hbox1->addWidget(Aa);
        vbox1->addItem(hbox1);
      }
      hbox->addItem(vbox1);
    }
    PointGroup = new QWidget();
    PointGroup->setLayout(hbox);
    vbox->addWidget(PointGroup);
  }
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Spot configuration"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    {
      QVBoxLayout* vbox1 = new QVBoxLayout();
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Angle "));
        hbox1->addWidget(SpotAngle);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("CosCutoff "));
        hbox1->addWidget(SpotCosCutoff);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Exponent "));
        hbox1->addWidget(SpotExponent);
        vbox1->addItem(hbox1);
      }
      hbox->addItem(vbox1);
    }
    SpotGroup = new QWidget();
    SpotGroup->setLayout(hbox);
    vbox->addWidget(SpotGroup);
  }
  vbox->addWidget(new QFormLine());
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Color"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    {
      QVBoxLayout* vbox1 = new QVBoxLayout();
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Ambient "));
        hbox1->addWidget(la);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Diffuse "));
        hbox1->addWidget(ld);
        vbox1->addItem(hbox1);
      }
      {
        QHBoxLayout* hbox1 = new QHBoxLayout();
        hbox1->addWidget(new QLabel("Specular "));
        hbox1->addWidget(ls);
        vbox1->addItem(hbox1);
      }
      hbox->addItem(vbox1);
    }
    vbox->addItem(hbox);
    vbox->addWidget(new QFormLine());
  }
  setLayout(vbox);

  QObject::connect(light_type,
                   SIGNAL(currentIndexChanged(int)),
                   this,
                   SLOT(changeLightType(int)));
  QObject::connect(la, SIGNAL(clicked()), this, SLOT(pickLaColor()));
  QObject::connect(ld, SIGNAL(clicked()), this, SLOT(pickLdColor()));
  QObject::connect(ls, SIGNAL(clicked()), this, SLOT(pickLsColor()));
  QObject::connect(Aa, SIGNAL(editingFinished()), this, SLOT(changeAa()));
  QObject::connect(Ab, SIGNAL(editingFinished()), this, SLOT(changeAb()));
  QObject::connect(Ac, SIGNAL(editingFinished()), this, SLOT(changeAc()));
  QObject::connect(
      SpotAngle, SIGNAL(editingFinished()), this, SLOT(changeSpotAngle()));
  QObject::connect(SpotCosCutoff,
                   SIGNAL(editingFinished()),
                   this,
                   SLOT(changeSpotCosCutoff()));
  QObject::connect(SpotExponent,
                   SIGNAL(editingFinished()),
                   this,
                   SLOT(changeSpotExponent()));
}

void LightEditPanel::setCurrentObject(rg::GLObject* O) {
  CurrentObject = static_cast<rg::GLLight*>(O);
  light_type->setCurrentIndex(CurrentObject->LightType);
  setButtonBackgroundColor(la, CurrentObject->La);
  setButtonBackgroundColor(ld, CurrentObject->Ld);
  setButtonBackgroundColor(ls, CurrentObject->Ls);

  if (CurrentObject->LightType == rg::GLLight::POINT)
    PointGroup->show();
  else
    PointGroup->hide();
  if (CurrentObject->LightType == rg::GLLight::SPOT)
    SpotGroup->show();
  else
    SpotGroup->hide();
  Aa->setText(QString::number(CurrentObject->Aa));
  Ab->setText(QString::number(CurrentObject->Ab));
  Ac->setText(QString::number(CurrentObject->Ac));
  SpotAngle->setText(QString::number(CurrentObject->SpotAngle));
  SpotCosCutoff->setText(QString::number(CurrentObject->SpotCosCutoff));
  SpotExponent->setText(QString::number(CurrentObject->SpotExponent));
}

glm::vec3 LightEditPanel::convertQColorToVec3(QColor color) {
  glm::vec3 vec;
  vec.r = color.red() / 255.0f;
  vec.g = color.green() / 255.0f;
  vec.b = color.blue() / 255.0f;
  return vec;
}

QColor LightEditPanel::convertVec3ToQColor(glm::vec3& vec) {
  QColor color;
  color.setRed(vec.r * 255);
  color.setGreen(vec.g * 255);
  color.setBlue(vec.b * 255);
  return color;
}

void LightEditPanel::setButtonBackgroundColor(QPushButton* button,
                                              glm::vec3& color) {
  QString Text;
  button->setStyleSheet(Text.sprintf(
      "QPushButton { border: 1px solid #000000; background-color: "
      "#%02x%02x%02x; }",
      int(color.x * 255),
      int(color.y * 255),
      int(color.z * 255)));
}

void LightEditPanel::changeLightType(int index) {
  if (CurrentObject)
    CurrentObject->LightType = index;
  if (index == 1)
    PointGroup->show();
  else
    PointGroup->hide();
  if (index == 2)
    SpotGroup->show();
  else
    SpotGroup->hide();
}

void LightEditPanel::pickLaColor() {
  QColorDialog* D = new QColorDialog(this);
  D->setCurrentColor(convertVec3ToQColor(CurrentObject->La));
  if (D->exec() == QDialog::Accepted) {
    CurrentObject->La = convertQColorToVec3(D->currentColor());
    setButtonBackgroundColor(la, CurrentObject->La);
  }
}

void LightEditPanel::pickLdColor() {
  QColorDialog* D = new QColorDialog(this);
  D->setCurrentColor(convertVec3ToQColor(CurrentObject->Ld));
  if (D->exec() == QDialog::Accepted) {
    CurrentObject->Ld = convertQColorToVec3(D->currentColor());
    setButtonBackgroundColor(ld, CurrentObject->Ld);
  }
}

void LightEditPanel::pickLsColor() {
  QColorDialog* D = new QColorDialog(this);
  D->setCurrentColor(convertVec3ToQColor(CurrentObject->Ls));
  if (D->exec() == QDialog::Accepted) {
    CurrentObject->Ls = convertQColorToVec3(D->currentColor());
    setButtonBackgroundColor(ls, CurrentObject->Ls);
  }
}

void LightEditPanel::changeAa() {
  if (CurrentObject)
    CurrentObject->Aa = Aa->text().toFloat();
}

void LightEditPanel::changeAb() {
  if (CurrentObject)
    CurrentObject->Ab = Ab->text().toFloat();
}

void LightEditPanel::changeAc() {
  if (CurrentObject)
    CurrentObject->Ac = Ac->text().toFloat();
}

void LightEditPanel::changeSpotAngle() {
  if (CurrentObject)
    CurrentObject->SpotAngle = SpotAngle->text().toFloat();
}

void LightEditPanel::changeSpotCosCutoff() {
  if (CurrentObject)
    CurrentObject->SpotCosCutoff = SpotCosCutoff->text().toFloat();
}

void LightEditPanel::changeSpotExponent() {
  if (CurrentObject)
    CurrentObject->SpotExponent = SpotExponent->text().toFloat();
}
