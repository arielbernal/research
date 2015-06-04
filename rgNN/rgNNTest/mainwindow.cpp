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
  connect(ui->btnTrain, SIGNAL(clicked()), this, SLOT(trainNN()));

  auto fp2 = std::bind(&MainWindow::Plot2DRenderer, this);
  ui->plot2d->setCallbackRenderer(fp2);

  T1 = new NNDataset<float, uint8_t>(2);

  std::vector<float> sample(2);
  for (size_t i = 0; i < 50; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.25 ;
    sample[1] = rand() / float(RAND_MAX) * 0.2f + 0.25+ i / 50.0f *0.5f;
    T1->addSample(sample, 0);
  }
  for (size_t i = 0; i < 50; ++i) {
    sample[0] = rand() / float(RAND_MAX) * 0.2f + 0.25 + i / 50.0f *0.5f;
    sample[1] = rand() / float(RAND_MAX) * 0.2f + 0.25 + i / 50.0f *0.5f;;
    T1->addSample(sample, 1);
  }


  nnff = new NNFeedForward<float>(2, 25, 2);
  auto fp1 = std::bind(&MainWindow::NNProgress, this, std::placeholders::_1,
                       std::placeholders::_2);
  nnff->setCallbackProgress(fp1);

  nnff->setTrainingAccuracy(1);
  nnff->setMaxEpochs(160000);
  nnff->setEpochStat(1000);

  ui->chartMSE->addGraph();
  ui->chartMSE->addGraph(ui->chartMSE->xAxis, ui->chartMSE->yAxis2);
  ui->chartMSE->xAxis->setLabel("Epochs");
  ui->chartMSE->yAxis->setLabel("MSE");
  ui->chartMSE->yAxis2->setLabel("Errors");
  ui->chartMSE->yAxis2->setVisible(true);
  ui->chartMSE->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                QCP::iSelectPlottables);
  ui->chartMSE->graph(0)->rescaleAxes();
  ui->chartMSE->graph(1)->rescaleAxes();
  ui->chartMSE->replot();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::trainNN() {
  nnff->train(T1);

  //  nnff->train(Training, 1);
  std::vector<float> output(2);
  for (size_t i = 0; i < 6; ++i) {
    float *p = T1->getSample(i);
    nnff->feedForward(p, output);
    std::cout << "----------------" << i << "-----------------" << std::endl;
    std::cout << p[0] << " " << p[1] << std::endl;
    std::cout << output[0] << " " << output[1] << std::endl;
  }
  std::cout << "new " << std::endl;
  float input[2] = { 0.2f, 0.8f };
  nnff->feedForward(input, output);
  std::cout << output[0] << " " << output[1] << std::endl;
  ui->plot2d->update();
}

void MainWindow::NNProgress(size_t i, NNStatistics &stat) {
  if (i % 100 == 0) {
    std::cout << " i = " << i << " mse = " << stat.MSE
              << " accuracy = " << stat.getAccuracy()
              << "  Errors = " << stat.Errors << std::endl;
    ui->chartMSE->graph(0)->addData(i, stat.MSE);
    ui->chartMSE->graph(0)->rescaleAxes();
    ui->chartMSE->graph(1)->addData(i, stat.Errors);
    ui->chartMSE->graph(1)->rescaleAxes();
    ui->chartMSE->replot();
  }
}

void MainWindow::Plot2DRenderer() {
  glTranslatef(0.1f, 0.1f, 0);
  size_t W = ui->plot2d->width();
  size_t H = ui->plot2d->height();
  std::vector<float> output(2);
  glPointSize(2);
  glBegin(GL_POINTS);
  for (size_t i = 0; i < T1->getN(); ++i) {
    T1->getLabel(i, output);
    if (output[0] == 1)
      glColor3f(0, 0, 0);
    if (output[1] == 1)
      glColor3f(1, 1, 1);
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
      float input[2] = { xx, yy };
      nnff->feedForward(input, output);
      if (output[0] > output[1])
        glColor3f(output[0], 0, 0);
      else
        glColor3f(0, output[1], 0);
      glVertex2f(x, y);
    }
  }
  glEnd();
}
