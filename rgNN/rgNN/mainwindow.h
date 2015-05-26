#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <nndataset.h>

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

protected:
  void FrameRenderer();
  void updateControls();

private:
  Ui::MainWindow *ui;
  NNDataset *Training;
};
#endif // MAINWINDOW_H
