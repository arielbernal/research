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

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(prevImage()));
  connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(nextImage()));
  connect(ui->edId, SIGNAL(textEdited(QString)), this, SLOT(currentImage()));
  connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadNN()));
  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveNN()));
  connect(ui->actionTrain, SIGNAL(triggered()), this, SLOT(trainNN()));
  connect(ui->btnTest, SIGNAL(clicked()), this, SLOT(testSampleNN()));

  Training = new NNDataset<uint8_t, uint8_t>(SAMPLE_COLS, SAMPLE_ROWS);

  auto fp = std::bind(&MainWindow::DigitRenderer, this);
  ui->glDigit->setCallbackRenderer(fp);

  Training->load(0, 600, "../data/train-images.idx3-ubyte",
                 "../data/train-labels.idx1-ubyte", 16, 8);
  updateControls();

  nnff = new NNFeedForward<double>(28 * 28, 60, 10);
  auto fp1 = std::bind(&MainWindow::NNProgress, this, std::placeholders::_1,
                       std::placeholders::_2);
  nnff->setCallbackProgress(fp1);

  ui->chartMSE->addGraph();
  ui->chartMSE->xAxis->setLabel("Epochs");
  ui->chartMSE->yAxis->setLabel("MSE");
  ui->chartMSE->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                QCP::iSelectPlottables);
  ui->chartMSE->graph(0)->rescaleAxes();
  ui->chartMSE->replot();

  ui->chartErrors->addGraph();
  ui->chartErrors->xAxis->setLabel("Epochs");
  ui->chartErrors->yAxis->setLabel("Errors");
  ui->chartErrors->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                   QCP::iSelectPlottables);
  ui->chartErrors->graph(0)->rescaleAxes();
  ui->chartErrors->graph(0)->setPen(QPen(QColor("#FFA100")));
  ui->chartErrors->replot();
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

void MainWindow::DigitRenderer() {
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
  if (Training->getN() > 0) {
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

void MainWindow::loadNN() {
  nnff->load("../data/NN.json");
  NNStatistics stat;
  nnff->statistics(Training, stat);
  std::cout << "Loaded statistics  Errors = " << stat.Errors << " MSE = " << stat.MSE << " Accuracy = "
            << stat.getAccuracy() << std::endl;
}

void MainWindow::saveNN() { nnff->save("../data/NN.json"); }

void MainWindow::trainNN() {
  nnff->setTrainingAccuracy(0.9);
  nnff->setLearningRate(0.0005);
  nnff->setMomentum(0.98);
  nnff->setMaxEpochs(1);
  nnff->setEpochStat(1);

  nnff->train(Training);
}

size_t getLabel(std::vector<double>& Result) {
  double vmax = Result[0];
  size_t imax = 0;
  for (size_t i = 0; i < Result.size(); ++i) {
    if (Result[i] > vmax) {
      vmax = Result[i];
      imax = i;
    }
  }
  return imax;
}

void MainWindow::testSampleNN() {
  std::vector<double> Result(10);
  nnff->feedForward(Training->getSample(), Result);
  std::cout << "FF = " << getLabel(Result) << std::endl;
}

void MainWindow::NNProgress(size_t i, NNStatistics& stat) {
  std::cout << " i = " << i << " mse = " << stat.MSE
            << " accuracy = " << stat.getAccuracy()
            << "  Errors = " << stat.Errors << std::endl;
  ui->chartMSE->graph(0)->addData(i, stat.MSE);
  ui->chartMSE->graph(0)->rescaleAxes();
  ui->chartMSE->replot();
  ui->chartErrors->graph(0)->addData(i, stat.Errors);
  ui->chartErrors->graph(0)->rescaleAxes();
  ui->chartErrors->replot();
}
