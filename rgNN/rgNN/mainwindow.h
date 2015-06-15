#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../common/nndataset.h>
#include <../common/nnclass.h>
#include <stdint.h>
#include <../common/trainingthread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
private slots:
  void prevImage();
  void nextImage();
  void currentImage();
  void startTraining();
  void stopTraining();
  void saveNN();
  void loadNN();
  void testSampleNN();
  void statTraining();
  void statTest();

protected:
  void DigitRenderer();
  void updateControls();
  void NNProgress(size_t i, NNStatistics<double> &stat);

  void trainNN();

private:
  Ui::MainWindow *ui;
  NNDataset<double, uint8_t> *Training;
  NNDataset<double, uint8_t> *Test;
  NNDataset<double, uint8_t> *Dataset;
  NNFeedForward<double> *nnff;
  TrainingThread<double, uint8_t>* TTrhead;
};
#endif // MAINWINDOW_H
