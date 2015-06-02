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

  auto fp2 = std::bind(&MainWindow::Plot2DRenderer, this);
  ui->plot2d->setCallbackRenderer(fp2);

  T1 = new NNDataset<float, uint8_t>(8, 2);
  float A[16] = {0, 0, 0, 1, 1, 0, 1, 1, 0.5f, 0.5f, 0.25f, 0.75f, 0.0f, 0.5f, 0.75f,0.75f};
  uint8_t l[8] = {0, 1, 1, 0, 0, 1, 0, 1};
  T1->load(A, 16, l, 8);

  nnff = new NNFeedForward(2, 10, 1, 2);
  auto fp1 = std::bind(&MainWindow::NNProgress,
                       this,
                       std::placeholders::_1,
                       std::placeholders::_2);
  nnff->setCallbackProgress(fp1);
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::trainNN() {
  nnff->train(T1, 40000);

  //  nnff->train(Training, 1);
  std::vector<float> output(2);
  for (size_t i = 0; i < 6; ++i) {
    float* p = T1->getSample(i);
    nnff->feedForward(p, output);
    std::cout << "----------------" << i << "-----------------" << std::endl;
    std::cout << p[0] << " " << p[1] << std::endl;
    std::cout << output[0] << " " << output[1] << std::endl;
  }
  std::cout << "new " << std::endl;
  float input[2] = {0.2f, 0.8f};
  nnff->feedForward(input, output);
  std::cout << output[0] << " " << output[1] << std::endl;
  ui->plot2d->update();
}

void MainWindow::NNProgress(size_t i, float mse) {
  std::cout << "Epoch = " << i << " mse = " << mse << std::endl;
}

void MainWindow::Plot2DRenderer() {
  glTranslatef(0.1f, 0.1f, 0);
  size_t W = ui->plot2d->width();
  size_t H = ui->plot2d->height();
  std::vector<float> output(2);
  glBegin(GL_POINTS);
  for (size_t y = 0; y < H; ++y) {
    for (size_t x = 0; x < W; ++x) {
      float yy = y / float(H);
      float xx = x / float(W);
      float input[2] = {xx, yy};
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
