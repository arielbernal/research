#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nndataset.h>
#include <nnclass.h>
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

protected:
  void DigitRenderer();
  void updateControls();

private:
  Ui::MainWindow *ui;
  NNDataset<uint8_t, uint8_t> *Training;
  NNDataset<float, uint8_t> *T1;
  NNFeedForward *nnff;
};
#endif // MAINWINDOW_H
