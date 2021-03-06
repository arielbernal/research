#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>

class ToolItem : public QWidget {
 public:
  ToolItem(const QString& title, QWidget* item, QWidget* parent = 0)
      : QWidget(parent), item(item) {
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    LabelTitle = new QLabel(title);
    LabelTitle->setStyleSheet(
        "QLabel {border: 2px solid green;"
        "border-radius: 4px;"
        "padding: 2px; font: bold; background-color : "
        "#777777; color : #EEEEEE; }");
    layout->addWidget(LabelTitle);
    layout->addWidget(item);
    setLayout(layout);
    item->setVisible(true);
    LabelTitle->installEventFilter(this);
  }
  QLabel* getTitle() { return LabelTitle; }
  void expand() { item->setVisible(true); }
  void collapse() { item->setVisible(false); }
  void hide() {
    collapse();
    LabelTitle->hide();
  }
  void show() {
    LabelTitle->show();
    expand();
  }

 protected:
  bool eventFilter(QObject* obj, QEvent* event) {
    if (obj == LabelTitle && event->type() == QEvent::MouseButtonPress) {
      item->setVisible(!item->isVisible());
      return true;
    }
    return false;
  }

 private:
  QWidget* item;
  QLabel* LabelTitle;
};

#endif  // TOOLITEM_H
