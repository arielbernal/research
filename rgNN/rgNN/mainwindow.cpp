#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>

#include <iostream>
#include <fstream>

#define SAMPLE_ROWS 28
#define SAMPLE_COLS 28
#define SAMPLE_SIZE (SAMPLE_ROWS * SAMPLE_COLS)
#define TRAINING_SAMPLES (60000)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(prevImage()));
  connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(nextImage()));
  connect(ui->edId, SIGNAL(textEdited(QString)), this, SLOT(currentImage()));
  connect(ui->btnTrain, SIGNAL(clicked()), this, SLOT(trainNN()));

  Training = new NNDataset(TRAINING_SAMPLES, SAMPLE_COLS, SAMPLE_ROWS);

  auto fp = std::bind(&MainWindow::FrameRenderer, this);
  ui->glDigit->setCallbackRenderer(fp);
  if (Training->isLoaded())
    return;
  Training->load("../data/train-images.idx3-ubyte", 16,
                 "../data/train-labels.idx1-ubyte", 8);
  updateControls();

  nnff = new NNFeedForward(28 * 28, 28 * 28, 1, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateControls() {
  ui->lbLabel->setText(QString::number(Training->getLabel()));
  ui->edId->setText(QString::number(Training->getCurrentId()));
  ui->glDigit->update();
}

void MainWindow::currentImage() {
  Training->setCurrentId(ui->edId->text().toLong());
  updateControls();
}

void MainWindow::prevImage() {
  Training->prev();
  updateControls();
}

void MainWindow::nextImage() {
  Training->next();
  updateControls();
}

void MainWindow::FrameRenderer() {
  float dx = ui->glDigit->width() / 28.05f;
  float dy = ui->glDigit->height() / 28.05f;
  glTranslatef(0.1, 0.1, 0);
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
  if (Training->isLoaded()) {
    glBegin(GL_QUADS);
    for (size_t y = 0; y < 28; ++y) {
      for (size_t x = 0; x < 28; ++x) {
        float pixelColor = Training->getXYValue(x, y) / 255.0f;
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

void MainWindow::trainNN() {

  nnff->train(Training, 1);
//  float output[10];
//  nnff->feedForward(Training->getSample(), output);
//  for (size_t i = 0; i < 10; ++i)
//      std::cout << output[i] << " ";
//  std::cout << std::endl;
}
