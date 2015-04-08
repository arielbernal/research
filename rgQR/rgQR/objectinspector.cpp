#include "objectinspector.h"

ObjectInspector::ObjectInspector(const QString &title, QWidget *parent,
                                 Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags) {

  QVBoxLayout *layout = new QVBoxLayout();

  Properties = new ToolBox();

  QWidget *QW = new QWidget();
  {
    PosX = new QLineEdit();
    PosX->setFixedWidth(70);
    PosY = new QLineEdit();
    PosY->setFixedWidth(70);
    PosZ = new QLineEdit();
    PosZ->setFixedWidth(70);
    RotX = new QLineEdit();
    RotX->setFixedWidth(70);
    RotY = new QLineEdit();
    RotY->setFixedWidth(70);
    RotZ = new QLineEdit();
    RotZ->setFixedWidth(70);
    ScaX = new QLineEdit();
    ScaX->setFixedWidth(70);
    ScaY = new QLineEdit();
    ScaY->setFixedWidth(70);
    ScaZ = new QLineEdit();
    ScaZ->setFixedWidth(70);
    QVBoxLayout *vbox = new QVBoxLayout();
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Position"));
      hbox->addSpacerItem(
          new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(PosX);
      hbox->addWidget(new QLabel("Y"));
      hbox->addWidget(PosY);
      hbox->addWidget(new QLabel("Z"));
      hbox->addWidget(PosZ);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Rotation"));
      QSpacerItem *item =
          new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(RotX);
      hbox->addWidget(new QLabel("Y"));
      hbox->addWidget(RotY);
      hbox->addWidget(new QLabel("Z"));
      hbox->addWidget(RotZ);
      vbox->addItem(hbox);
    }
    QW->setLayout(vbox);
    Properties->addItem(new ToolItem("Transform", QW));
  }

  QHBoxLayout *hbox1 = new QHBoxLayout();
  hbox1->addWidget(new QLabel("Name:"));
  hbox1->addWidget(new QLineEdit());

  layout->addLayout(hbox1);
  layout->addWidget(Properties);
  QWidget *QW1 = new QWidget();
  QW1->setLayout(layout);
  setWidget(QW1);
}

ObjectInspector::~ObjectInspector() {}
