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
  connect(ui->btnErrPrev, SIGNAL(clicked()), this, SLOT(errPrev()));
  connect(ui->btnErrNext, SIGNAL(clicked()), this, SLOT(errNext()));

  connect(ui->edId, SIGNAL(textEdited(QString)), this, SLOT(currentImage()));
  connect(ui->btnTest, SIGNAL(clicked()), this, SLOT(testSampleNN()));
  connect(ui->btnStatTraining, SIGNAL(clicked()), this, SLOT(statTraining()));
  connect(ui->btnStatTest, SIGNAL(clicked()), this, SLOT(statTest()));
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

  auto fp = std::bind(&MainWindow::DigitRenderer, this);
  ui->glDigit->setCallbackRenderer(fp);

  Training = new NNDataset<double, uint8_t>(SAMPLE_COLS, SAMPLE_ROWS, 10);
  Test = new NNDataset<double, uint8_t>(SAMPLE_COLS, SAMPLE_ROWS, 10);
  Dataset = Training;

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

  Test->setMeanVector(Training->getMeanVector());
  Test->normalizeInputs();
  Test->processInputs();

  updateControls();

  nnff = new NNFeedForward<double>(28 * 28, 600, 10);
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
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::updateControls() {
  ui->lbLabel->setText(QString::number(Dataset->getLabel()));
  ui->edId->setText(QString::number(Dataset->getCurrentId()));
  ui->glDigit->update();
}

void MainWindow::currentImage() {
  Dataset->setCurrentId(ui->edId->text().toLong());
  updateControls();
}

void MainWindow::prevImage() {
  Dataset->prev();
  updateControls();
}

void MainWindow::nextImage() {
  Dataset->next();
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

void MainWindow::errPrev() {
  if (!stat.ErrorIds.empty()) {
    if (statId > 0)
      statId--;
    Dataset->setCurrentId(stat.ErrorIds[statId]);
  }
  updateControls();
}

void MainWindow::errNext() {
  if (!stat.ErrorIds.empty()) {
    if (statId < stat.ErrorIds.size() - 1)
      statId++;
    Dataset->setCurrentId(stat.ErrorIds[statId]);
  }
  updateControls();
}

void MainWindow::statTraining() {
  Dataset = Training;
  nnff->statistics(Training, stat);
  std::cout << "Training statistics  Errors = " << stat.Errors
            << " MSE = " << stat.MSE << " Accuracy = " << stat.getAccuracy()
            << " Error = " << (1 - stat.getAccuracy()) * 100 << "%"
            << std::endl;
  if (!stat.ErrorIds.empty()) {
    Dataset->setCurrentId(stat.ErrorIds[0]);
    updateControls();
  }
}

void MainWindow::statTest() {
  Dataset = Test;
  nnff->statistics(Test, stat);
  std::cout << "Test statistics  Errors = " << stat.Errors
            << " MSE = " << stat.MSE << " Accuracy = " << stat.getAccuracy()
            << " Error = " << (1 - stat.getAccuracy()) * 100 << "%"
            << std::endl;
  if (!stat.ErrorIds.empty()) {
    Dataset->setCurrentId(stat.ErrorIds[0]);
    updateControls();
  }
}

void MainWindow::loadNN() {
  nnff->load("../data/MNIST/NN.json");
  NNStatistics<double> stat;
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
  nnff->setLearningRate(0.0001);
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
  nnff->feedForward(Dataset->getInput(), Result.data());
  std::cout << "FF = " << getLabel(Result) << "  -- ";
  for (size_t i = 0; i < Result.size(); ++i)
    printf("%6.4f ", Result[i]);
  std::cout << std::endl;
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
