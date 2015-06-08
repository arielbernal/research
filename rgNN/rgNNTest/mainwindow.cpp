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
  connect(ui->btnTrain, SIGNAL(clicked()), this, SLOT(trainNN()));
  connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveNN()));
  connect(ui->btnLoad, SIGNAL(clicked()), this, SLOT(loadNN()));

  auto fp2 = std::bind(&MainWindow::Plot2DRenderer, this);
  ui->plot2d->setCallbackRenderer(fp2);

  T1 = new NNDataset<float, uint8_t>(2);

  std::vector<float> sample(2);
  for (size_t i = 0; i < 150; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.25;
    sample[1] = rand() / float(RAND_MAX) * 0.2f + 0.25 + i / 50.0f * 0.5f;
    T1->addSample(sample, 0);
  }
  for (size_t i = 0; i < 150; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.5;
    sample[1] = rand() / float(RAND_MAX) * 0.2f;
    T1->addSample(sample, 0);
  }
  for (size_t i = 0; i < 150; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.25 + i / 50.0f * 0.5f;
    sample[1] = rand() / float(RAND_MAX) * 0.2f + 0.25 + i / 50.0f * 0.5f;
    T1->addSample(sample, 1);
  }
  for (size_t i = 0; i < 150; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.75;
    sample[1] = rand() / float(RAND_MAX) * 0.2f + 0.25;
    T1->addSample(sample, 2);
  }

  T1->randomizeOrder();

  nnff = new NNFeedForward<float>(2, 2, 3, 1);
  auto fp1 = std::bind(&MainWindow::NNProgress,
                       this,
                       std::placeholders::_1,
                       std::placeholders::_2);
  nnff->setCallbackProgress(fp1);

  nnff->setTrainingAccuracy(0.98);
  nnff->setMaxEpochs(16000);
  nnff->setEpochStat(100);

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

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::trainNN() {
  nnff->train(T1);
  ui->plot2d->update();
}

void MainWindow::loadNN() {
  nnff->load("../data/test.nn");
}

void MainWindow::saveNN() {
  nnff->save("../data/test.nn");
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

void MainWindow::Plot2DRenderer() {
  glTranslatef(0.1f, 0.1f, 0);
  size_t W = ui->plot2d->width();
  size_t H = ui->plot2d->height();
  std::vector<float> output(3);
  glPointSize(2);
  glBegin(GL_POINTS);
  for (size_t i = 0; i < T1->getN(); ++i) {
    T1->getLabel(i, output);
    glColor3f(output[1], output[2], output[0]);
    float xx = T1->getSample(i)[0];
    float yy = T1->getSample(i)[1];
    glVertex2f(xx * (W - 1), yy * (H - 1));
  }
  glEnd();
  glPointSize(0);

  glBegin(GL_POINTS);
  for (size_t y = 0; y < H; ++y) {
    for (size_t x = 0; x < W; ++x) {
      float yy = y / float(H);
      float xx = x / float(W);
      float input[2] = {xx, yy};
      nnff->feedForward(input, output);
      glColor3f(output[0], output[1], output[2]);
      glVertex2f(x, y);
    }
  }
  glEnd();
}
