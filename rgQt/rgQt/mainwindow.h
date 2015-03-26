#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gl/rgGLScene.h>
#include <gl/rgGLObject.h>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(rg::GLScene &S, QWidget *parent = 0);

  ~MainWindow();

  void buildTree(QTreeWidget *tree, QTreeWidgetItem *item, rg::GLObject *Node);
public slots:
  void GLWidgetInitialized();

private:
  Ui::MainWindow *ui;
  rg::GLScene &Scene;
};

#endif // MAINWINDOW_H
