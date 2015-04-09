#ifndef VALLINEEDIT_H
#define VALLINEEDIT_H

#include <QDoubleValidator>
#include <QLineEdit>

class ValLineEdit : public QLineEdit {
public:
  ValLineEdit(int width, QWidget *parent = 0) : QLineEdit(parent) {
    setFixedWidth(width);
    setAlignment(Qt::AlignRight);
    QDoubleValidator *DV = new QDoubleValidator();
    DV->setDecimals(4);
    setValidator(DV);
  }
};

#endif // VALLINEEDIT_H

