#ifndef VALLINEEDIT_H
#define VALLINEEDIT_H

#include <QDoubleValidator>
#include <QLineEdit>

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

#endif  // VALLINEEDIT_H
