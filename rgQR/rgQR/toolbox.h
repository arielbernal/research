#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <toolitem.h>

class ToolBox : public QWidget {
 public:
  ToolBox(QWidget* parent = 0) : QWidget(parent), layout(new QVBoxLayout) {
    setLayout(layout);
  }

  void addItem(ToolItem* item) {
    int count = layout->count();
    if (count > 1)
      layout->removeItem(layout->itemAt(count - 1));
    layout->addWidget(item);
    layout->addStretch();
  }
  void hideItem(int index) {
    layout->itemAt(index)->widget()->setVisible(false);
  }

  ToolItem* itemAt(int index) {
    return static_cast<ToolItem*>(layout->itemAt(index)->widget());
  }

 private:
  QVBoxLayout* layout;
};

#endif  // TOOLBOX_H
