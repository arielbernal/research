#ifndef DATASETVIEWER_H
#define DATASETVIEWER_H

#include <QDialog>
#include <iostream>
#include <../common/nndataset.h>

namespace Ui {
class DatasetViewer;
}

class DatasetViewer : public QDialog {
  Q_OBJECT

 public:
  explicit DatasetViewer(const std::string& Name,
                         NNDataset1<>* Dataset,
                         QWidget* parent = 0);
  ~DatasetViewer();

 protected:
  void closeEvent(QCloseEvent* event);
  void DigitRenderer();
 private:
  Ui::DatasetViewer* ui;
  std::string Name;
  NNDataset1<>* Dataset;
};

#endif  // DATASETVIEWER_H
