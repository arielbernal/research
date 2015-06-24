#include <../common/datasetviewer.h>
#include "ui_datasetviewer.h"
#include <iostream>

DatasetViewer::DatasetViewer(const std::string& Name,
                             NNDataset1<>* Dataset,
                             QWidget* parent)
    : QDialog(parent), ui(new Ui::DatasetViewer), Name(Name), Dataset(Dataset) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  setModal(false);
  setWindowTitle(Name.c_str());

  connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(prevImage()));
  connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(nextImage()));
  connect(ui->btnFirst, SIGNAL(clicked()), this, SLOT(firstImage()));
  connect(ui->btnLast, SIGNAL(clicked()), this, SLOT(lastImage()));

  auto fp = std::bind(&DatasetViewer::DigitRenderer, this);
  ui->glDigit->setCallbackRenderer(fp);
}

DatasetViewer::~DatasetViewer() {
  delete ui;
}

void DatasetViewer::closeEvent(QCloseEvent* event) {
}

void DatasetViewer::DigitRenderer() {
  float dx = ui->glDigit->width() / 28.05f;
  float dy = ui->glDigit->height() / 28.05f;
  glTranslatef(0.1f, 0.1f, 0);
  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  for (size_t x = 0; x <= 28; ++x) {
    glVertex2f(x * dx, 0);
    glVertex2f(x * dx, 28 * dy);
  }
  for (size_t y = 0; y <= 28; ++y) {
    glVertex2f(0, (28 - y) * dy);
    glVertex2f(28 * dx, (28 - y) * dy);
  }
  glEnd();
  glColor3f(1, 1, 1);
  if (Dataset->getN() > 0) {
    glBegin(GL_QUADS);
    for (size_t y = 0; y < 28; ++y) {
      for (size_t x = 0; x < 28; ++x) {
        float pixelColor = Dataset->getXYValue(x, y) / 255.0f;
        glColor3f(pixelColor, pixelColor, pixelColor);
        glVertex2f(x * dx, (28 - y) * dy);
        glVertex2f((x + 1) * dx, (28 - y) * dy);
        glVertex2f((x + 1) * dx, (28 - y + 1) * dy);
        glVertex2f(x * dx, (28 - y + 1) * dy);
      }
    }
    glEnd();
  }
}

void DatasetViewer::updateControls() {
  ui->edIndex->setText(QString::number(Dataset->getCurrentId()));
  ui->edN->setText(QString::number(Dataset->getN()-1));
  ui->edSampleId->setText(QString::number(Dataset->getCurrentSampleId()));
  ui->glDigit->update();
}

void DatasetViewer::nextImage() {
  Dataset->next();
  updateControls();
}

void DatasetViewer::prevImage() {
  Dataset->prev();
  updateControls();
}

void DatasetViewer::firstImage() {
  Dataset->first();
  updateControls();
}

void DatasetViewer::lastImage() {
  Dataset->last();
  updateControls();
}
