#ifndef QFORMLINE_H
#define QFORMLINE_H

#include <QFrame>

class QFormLine : public QFrame {
 public:
  enum { HORIZONTAL, VERTICAL };
  QFormLine(int type = HORIZONTAL, bool sunken = true);
  ~QFormLine();
};

#endif  // QFORMLINE_H
