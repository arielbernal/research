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
  void trainNN();

protected:
  void Plot2DRenderer();
  void NNProgress(size_t i, NNStatistics& stat);

private:
  Ui::MainWindow *ui;
  NNDataset<float, uint8_t> *T1;
  NNFeedForward<float> *nnff;
};
#endif // MAINWINDOW_H
