#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nndataset.h>
#include <nnclass.h>


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
  void FrameRenderer();
  void updateControls();

private:
  Ui::MainWindow *ui;
  NNDataset *Training;
  NNFeedForward *nnff;
};
#endif // MAINWINDOW_H
