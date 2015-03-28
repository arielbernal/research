#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <gl/rgGLScene.h>
#include <gl/rgGLObject.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(rg::GLScene& S, QWidget* parent = 0);
  ~MainWindow();
  void buildTree(QTreeWidget* tree, QTreeWidgetItem* item, rg::GLObject* Node);
 public slots:
  void GLWidgetInitialized();
 private slots:
  void on_actionExit_triggered();

  void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
  Ui::MainWindow* ui;
  rg::GLScene& Scene;
};

#endif  // MAINWINDOW_H
