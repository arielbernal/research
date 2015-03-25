#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gl/rgGLScene.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(rg::GLScene &S, QWidget *parent = 0);

  ~MainWindow();

  void slotFromSomeone() {}

private:
  Ui::MainWindow *ui;
  rg::GLScene &Scene;
};

#endif // MAINWINDOW_H
