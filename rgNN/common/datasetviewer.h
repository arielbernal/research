#ifndef DATASETVIEWER_H
#define DATASETVIEWER_H

#include <QDialog>
#include <iostream>

namespace Ui {
class DatasetViewer;
}

class DatasetViewer : public QDialog {
  Q_OBJECT

 public:
  explicit DatasetViewer(const std::string& Name, QWidget* parent = 0);
  ~DatasetViewer();

 protected:
  void closeEvent(QCloseEvent* event);

 private:
  Ui::DatasetViewer* ui;
  std::string Name;
};

#endif  // DATASETVIEWER_H
