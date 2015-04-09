#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QDataWidgetMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
  QStandardItemModel* model;
  QDataWidgetMapper* mapper;

  QStandardItemModel* modelObjects;
  QDataWidgetMapper* mapperObjects;
  void on_editPosX_editingFinished();
  void on_treeView_clicked(const QModelIndex& index);

private:
  Ui::MainWindow* ui;
};



#endif  // MAINWINDOW_H
