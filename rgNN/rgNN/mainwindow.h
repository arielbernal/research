#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <../common/nndataset.h>
#include <../common/nnclass.h>
#include <stdint.h>

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
  void trainNN();
  void saveNN();
  void loadNN();
  void testSampleNN();

protected:
  void DigitRenderer();
  void updateControls();
  void NNProgress(size_t i, NNStatistics &stat);

private:
  Ui::MainWindow *ui;
  NNDataset<uint8_t, uint8_t> *Training;
  NNFeedForward<double> *nnff;
};
#endif // MAINWINDOW_H
