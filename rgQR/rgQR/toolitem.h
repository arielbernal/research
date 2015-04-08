#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>

class ToolItem : public QWidget {
public:
  ToolItem(const QString &title, QWidget *item, QWidget *parent = 0)
      : item(item), QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    LabelTitle = new QLabel(title);
    LabelTitle->setStyleSheet("QLabel {border: 2px solid green;"
                              "border-radius: 4px;"
                              "padding: 2px; font: bold; background-color : "
                              "#777777; color : #CCCCCC; }");
    layout->addWidget(LabelTitle);
    layout->addWidget(item);
    setLayout(layout);
    item->setVisible(false);
  }

  QLabel *getTitle() { return LabelTitle; }

protected:
  void mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
      item->setVisible(!item->isVisible());
  }

private:
  QWidget *item;
  QLabel *LabelTitle;
};

#endif // TOOLITEM_H
