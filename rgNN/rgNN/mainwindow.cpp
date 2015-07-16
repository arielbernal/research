#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>

#include <iostream>
#include <fstream>

#include <../common/datasetviewer.h>

#define SAMPLE_ROWS 28
#define SAMPLE_COLS 28
#define SAMPLE_SIZE (SAMPLE_ROWS * SAMPLE_COLS)
#define TRAINING_SAMPLES (60000)

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadNN()));
  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveNN()));
  connect(ui->actionStartTraining,
          SIGNAL(triggered()),
          this,
          SLOT(startTraining()));
  connect(
      ui->actionStopTraining, SIGNAL(triggered()), this, SLOT(stopTraining()));

  ui->actionStopTraining->setDisabled(true);

  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateGraphs()));
  timer->start(50);

  Training = new NNDataset<double, uint8_t>(28, 28, 10);
  Test = new NNDataset<double, uint8_t>(28, 28, 10);
  Training->load(0,
                 60000,
                 "../data/train-images.idx3-ubyte",
                 "../data/train-labels.idx1-ubyte",
                 16,
                 8);

  Test->load(0,
             10000,
             "../data/t10k-images.idx3-ubyte",
             "../data/t10k-labels.idx1-ubyte",
             16,
             8);
  Test->setMeanSample(Training->getMeanSample());
  Test->normalizeInputs();
  Test->processInputs();

  nnff = new NNFeedForward<double>(28 * 28, 300, 10);
  auto fp1 = std::bind(&MainWindow::NNProgress,
                       this,
                       std::placeholders::_1,
                       std::placeholders::_2);
  nnff->setCallbackProgress(fp1);

  TTrhead = new TrainingThread<double, uint8_t>(nnff, Training);

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
  statId = 0;
  isGraphUpdated = false;

  pDialogTesting = new DatasetViewer("Testing Dataset", Test, nnff);
  pDialogTesting->show();
  pDialogTraining = new DatasetViewer("Training Dataset", Training, nnff);
  pDialogTraining->show();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent*) {
  if (pDialogTesting)
    pDialogTesting->close();
  if (pDialogTraining)
    pDialogTraining->close();
}

void MainWindow::loadNN() {
  nnff->load("../data/MNIST/NN.json");
  nnff->statistics(Test, stat);
  std::cout << "Loaded statistics  Errors = " << stat.Errors
            << " MSE = " << stat.MSE << " Accuracy = " << stat.getAccuracy()
            << " Error = " << (1 - stat.getAccuracy()) * 100 << "%"
            << std::endl;
}

void MainWindow::saveNN() {
  nnff->save("../data/MNIST/NN.json");
}

void MainWindow::startTraining() {
  nnff->setTrainingAccuracy(2 + 1 - 0.0001);
  nnff->setLearningRate(0.0005);
  nnff->setMomentum(0.9);
  nnff->setMaxEpochs(10000);
  nnff->setEpochStat(2);
  TTrhead->start();
  ui->actionStartTraining->setDisabled(true);
  ui->actionStopTraining->setDisabled(false);
}

#ifdef Q_OS_WIN
#include <windows.h>  // for Sleep
#endif
void qSleep(int ms) {
#ifdef Q_OS_WIN
  Sleep(uint(ms));
#else
  struct timespec ts = {ms / 1000, (ms % 1000) * 1000 * 1000};
  nanosleep(&ts, NULL);
#endif
}

void MainWindow::stopTraining() {
  TTrhead->stopTraining();
  while (!TTrhead->isStopped()) {
    qSleep(10);
  }
  ui->actionStartTraining->setDisabled(false);
  ui->actionStopTraining->setDisabled(true);
}

void MainWindow::NNProgress(size_t i, NNStatistics<double>& Stat) {
  //  if (i % 10 == 0) {
  //    char str[200];
  //    sprintf(str, "../data/MNIST/FFNN%i.json", i);
  //    nnff->save(str);
  //    //    double lr = nnff->getLearningRate() * 0.9f;
  //    //    nnff->setLearningRate(lr);
  //  }
  // std::cout << "--------------------------------------------------\n"
  if (i % 4 == 0) {
    nnff->statistics(Test, stat);
    std::cout << "Test statistics  Errors = " << stat.Errors
              << " MSE = " << stat.MSE << " Accuracy = " << stat.getAccuracy()
              << " Error = " << (1 - stat.getAccuracy()) * 100 << "%"
              << std::endl;
  }
  std::cout << "i = " << i << " Learning = " << nnff->getLearningRate()
            << " MSE = " << Stat.MSE << " Accuracy = " << Stat.getAccuracy()
            << " Error = " << (1 - Stat.getAccuracy()) * 100 << "%"
            << " Errors = "
            << Stat.Errors
            //<< "\n--------------------------------------------------"
            << std::endl;
  ui->chartMSE->graph(0)->addData(i, Stat.MSE);
  ui->chartMSE->graph(0)->rescaleAxes();
  ui->chartErrors->graph(0)->addData(i, Stat.Errors);
  ui->chartErrors->graph(0)->rescaleAxes();
  isGraphUpdated = true;
}

void MainWindow::updateGraphs() {
  if (isGraphUpdated) {
    ui->chartMSE->replot();
    ui->chartErrors->replot();
    isGraphUpdated = false;
  }
}
