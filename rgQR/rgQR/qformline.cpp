#include "qformline.h"

QFormLine::QFormLine(int type, bool sunken) {
  if (type == HORIZONTAL)
    setFrameShape(QFrame::HLine);
  else
    setFrameShape(QFrame::VLine);
  if (sunken)
    setFrameShadow(QFrame::Sunken);
}

QFormLine::~QFormLine() {}
