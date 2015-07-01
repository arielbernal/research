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
  void startTraining();
  void stopTraining();
  void saveNN();
  void loadNN();
  void updateGraphs();

protected:
  void NNProgress(size_t i, NNStatistics<double> &stat);
  void trainNN();

private:
  Ui::MainWindow *ui;
  NNDataset<double, uint8_t> *Training;
  NNDataset<double, uint8_t> *Test;
  NNStatistics<double> stat;
  NNFeedForward<double> *nnff;
  TrainingThread<double, uint8_t>* TTrhead;
  size_t statId;
  bool isGraphUpdated;
};
#endif // MAINWINDOW_H
