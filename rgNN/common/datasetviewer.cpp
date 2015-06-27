#include <../common/datasetviewer.h>
#include "ui_datasetviewer.h"
#include <iostream>

DatasetViewer::DatasetViewer(const std::string& Name,
                             NNDataset1<>* Dataset,
                             NNFeedForward<>* NNFF,
                             QWidget* parent)
    : QDialog(parent),
      ui(new Ui::DatasetViewer),
      Name(Name),
      Dataset(Dataset),
      NNFF(NNFF) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
  setModal(false);
  setWindowTitle(Name.c_str());

  connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(prevImage()));
  connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(nextImage()));
  connect(ui->btnFirst, SIGNAL(clicked()), this, SLOT(firstImage()));
  connect(ui->btnLast, SIGNAL(clicked()), this, SLOT(lastImage()));
  connect(ui->btnApplyFilter, SIGNAL(clicked()), this, SLOT(applyFilter()));
  connect(ui->btnClearFilter, SIGNAL(clicked()), this, SLOT(clearFilter()));
  connect(ui->btnUpdateStats, SIGNAL(clicked()), this, SLOT(updateStats()));
  connect(ui->edIndex,
          SIGNAL(textChanged(QString)),
          this,
          SLOT(editIndex(QString)));

  auto fp = std::bind(&DatasetViewer::DigitRenderer, this);
  ui->glDigit->setCallbackRenderer(fp);

  Iterator = Dataset->begin();
  updateControls();
}

DatasetViewer::~DatasetViewer() {
  delete ui;
}

void DatasetViewer::closeEvent(QCloseEvent* event) {
}

void DatasetViewer::DigitRenderer() {
  if (Iterator == Dataset->end())
    return;
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
        float pixelColor = (*Iterator)->Data[x + y * 28] / 255.0f;
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
  if (Iterator == Dataset->end())
    return;

  ui->edIndex->setText(QString::number((Iterator - Dataset->begin())));
  ui->edN->setText(QString::number(Dataset->getN()));
  ui->edSampleId->setText(QString::number(((*Iterator)->Id)));
  ui->edSamplesN->setText(QString::number(Dataset->getNSamples()));
  ui->lbLabel->setText(QString::number((*Iterator)->Label));
  ui->glDigit->update();
}

void DatasetViewer::nextImage() {
  if (Dataset->getN() > 0) {
    Iterator++;
    if (Iterator == Dataset->end())
      --Iterator;
  }
  updateControls();
}

void DatasetViewer::prevImage() {
  if (Dataset->getN() > 0 && Iterator != Dataset->begin()) {
    Iterator--;
    updateControls();
  }
}

void DatasetViewer::firstImage() {
  if (Dataset->getN() > 0) {
    Iterator = Dataset->begin();
    updateControls();
  }
}

void DatasetViewer::lastImage() {
  if (Dataset->getN() > 0) {
    Iterator = Dataset->end() - 1;
    updateControls();
  }
}

void DatasetViewer::editIndex(QString text) {
  int i = text.toInt();
  if (i >= 0 && i < Dataset->getN()) {
    Iterator = Dataset->begin() + i;
  }
  updateControls();
}

void DatasetViewer::applyFilter() {
  char A[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (size_t i = 0; i < 10; ++i) {
    std::string a(1, A[i]);
    if (ui->listFilter->currentItem()->text() == QString::fromStdString(a)) {
      Dataset->addFilterByLabel(i);
    }
  }
  if (ui->listFilter->currentItem()->text() == QString("Errors")) {
    Dataset->addFilterByError();
  }
  ui->lbAppliedFilter->setText("Active");
  Iterator = Dataset->begin();
  updateControls();
}

void DatasetViewer::clearFilter() {
  Dataset->clearFilter();
  ui->lbAppliedFilter->setText("None");
  Iterator = Dataset->begin();
  updateControls();
}

void DatasetViewer::updateStats() {
  NNFF->statistics(Dataset, Stat);
  std::cout << "Test statistics  Errors = " << Stat.Errors
            << " MSE = " << Stat.MSE << " Accuracy = " << Stat.getAccuracy()
            << " Error = " << (1 - Stat.getAccuracy()) * 100 << "%"
            << std::endl;
  updateControls();
}
