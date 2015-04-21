#include <lighteditpanel.h>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <qformline.h>
#include <QDebug>

#include <gl/rgglcamera.h>

LightEditPanel::LightEditPanel()
    : light_type(new QComboBox), la(new QPushButton()) {
  la->setStyleSheet("QPushButton { border: 1px solid #000000;}");
  la->setFlat(true);
  la->setFixedWidth(200);

  QObject::connect(la, SIGNAL(clicked()), this, SLOT(pickLaColor()));

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
    vbox->addWidget(new QFormLine());
  }
  {
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Color"));
    hbox->addSpacerItem(new QSpacerItem(
        20, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    hbox->addWidget(la);
    vbox->addItem(hbox);
    vbox->addWidget(new QFormLine());
  }
  setLayout(vbox);
}

void LightEditPanel::setCurrentObject(rg::GLObject* O) {
  CurrentObject = static_cast<rg::GLLight*>(O);
  setButtonBackgroundColor(la, CurrentObject->La);

  //  projection->setCurrentIndex(CurrentObject->projection);
  //  view_h->setText(QString::number(CurrentObject->view_h));
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

void LightEditPanel::setButtonBackgroundColor(QPushButton* button, glm::vec3& color) {
    QString Text;
    button->setStyleSheet(Text.sprintf(
        "QPushButton { border: 1px solid #000000; background-color: #%02x%02x%02x; }",
        int(color.x * 255),
        int(color.y * 255),
        int(color.z * 255)));
}

void LightEditPanel::pickLaColor() {
  QColorDialog* D = new QColorDialog(this);
  D->setOption(QColorDialog::DontUseNativeDialog);
  D->setCurrentColor(convertVec3ToQColor(CurrentObject->La));
  if (D->exec() == QDialog::Accepted) {
    CurrentObject->La = convertQColorToVec3(D->currentColor());
    setButtonBackgroundColor(la, CurrentObject->La);
  }
}
