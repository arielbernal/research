#ifndef VALLINEEDIT_H
#define VALLINEEDIT_H

#include <QLineEdit>
#include <QDoubleValidator>

class EditDouble : public QLineEdit {
 public:
  EditDouble(int width, int decimals = 4, QWidget* parent = 0)
      : QLineEdit(parent) {
    setFixedWidth(width);
    setAlignment(Qt::AlignRight);
    QDoubleValidator* DV = new QDoubleValidator();
    DV->setDecimals(decimals);
    setValidator(DV);
  }
};


class EditInteger : public QLineEdit {
 public:
  EditInteger(int width, QWidget* parent = 0)
      : QLineEdit(parent) {
    setFixedWidth(width);
    setAlignment(Qt::AlignRight);
  }
};

#endif  // VALLINEEDIT_H
