#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <toolitem.h>

class ToolBox : public QWidget {
 public:
  ToolBox(QWidget* parent = 0) : QWidget(parent), layout(new QVBoxLayout) {
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(layout);
  }

  void addItem(ToolItem* item) {
    int count = layout->count();
    if (count > 1)
      layout->removeItem(layout->itemAt(count - 1));
    layout->addWidget(item);
    layout->addStretch();
  }
  void collapseItem(int index) {
    ToolItem* item = static_cast<ToolItem*>(layout->itemAt(index)->widget());
    item->collapse();
  }
  void expandItem(int index) {
    ToolItem* item = static_cast<ToolItem*>(layout->itemAt(index)->widget());
    item->expand();
  }
  void hideItem(int index) {
    ToolItem* item = static_cast<ToolItem*>(layout->itemAt(index)->widget());
    item->hide();
  }
  void showItem(int index) {
    ToolItem* item = static_cast<ToolItem*>(layout->itemAt(index)->widget());
    item->show();
  }

  ToolItem* itemAt(int index) {
    return static_cast<ToolItem*>(layout->itemAt(index)->widget());
  }

  void hideAll() {
    for (int i = 0; i < layout->count() - 1; ++i) {
      ToolItem* item = static_cast<ToolItem*>(layout->itemAt(i)->widget());
      item->hide();
    }
  }

 private:
  QVBoxLayout* layout;
};

#endif  // TOOLBOX_H
