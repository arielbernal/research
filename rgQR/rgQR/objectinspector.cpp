#include "objectinspector.h"
#include <QDoubleValidator>

ObjectInspector::ObjectInspector(const QString &title, QWidget *parent,
                                 Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags) {

  QVBoxLayout *layout = new QVBoxLayout();

  Properties = new ToolBox();
  ObjectName = new QLineEdit();
  PosX = new ValLineEdit(70);
  PosY = new ValLineEdit(70);
  PosZ = new ValLineEdit(70);
  RotX = new ValLineEdit(70);
  RotY = new ValLineEdit(70);
  RotZ = new ValLineEdit(70);
  ScaX = new ValLineEdit(70);
  ScaY = new ValLineEdit(70);
  ScaZ = new ValLineEdit(70);

  {
    QVBoxLayout *vbox = new QVBoxLayout();
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Position"));
      hbox->addSpacerItem(new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed));
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(PosX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(PosY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(PosZ);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Rotation"));
      QSpacerItem *item = new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(RotX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(RotY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(RotZ);
      vbox->addItem(hbox);
    }
    {
      QHBoxLayout *hbox = new QHBoxLayout();
      hbox->addWidget(new QLabel("Scaling"));
      QSpacerItem *item = new QSpacerItem(20, 1, QSizePolicy::MinimumExpanding,
                                          QSizePolicy::Fixed);
      hbox->addSpacerItem(item);
      hbox->addWidget(new QLabel("X"));
      hbox->addWidget(ScaX);
      hbox->addWidget(new QLabel(" Y"));
      hbox->addWidget(ScaY);
      hbox->addWidget(new QLabel(" Z"));
      hbox->addWidget(ScaZ);
      vbox->addItem(hbox);
    }
    QWidget *QW = new QWidget();
    QW->setLayout(vbox);
    Properties->addItem(new ToolItem("Transform", QW));
  }

  {
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(new QLabel("Name:"));
    hbox->addWidget(ObjectName);
    layout->addLayout(hbox);
  }
  layout->addWidget(Properties);
  QWidget *QW = new QWidget();
  QW->setLayout(layout);
  setWidget(QW);
}

ObjectInspector::~ObjectInspector() {}

void ObjectInspector::SetObjectValues() {}
