#ifndef DATASETVIEWER_H
#define DATASETVIEWER_H

#include <QDialog>
#include <iostream>
#include <../common/nndataset.h>
#include <../common/nnclass.h>

namespace Ui {
class DatasetViewer;
}

class DatasetViewer : public QDialog {
  Q_OBJECT

 public:
  explicit DatasetViewer(const std::string& Name,
                         NNDataset1<>* Dataset,
                         NNFeedForward<>* NNFF,
                         QWidget* parent = 0);
  ~DatasetViewer();
 private slots:
  void prevImage();
  void nextImage();
  void firstImage();
  void lastImage();
  void applyFilter();
  void clearFilter();
  void updateStats();

 protected:
  void closeEvent(QCloseEvent* event);
  void DigitRenderer();
  void updateControls();

 private:
  Ui::DatasetViewer* ui;
  std::string Name;
  NNDataset1<>* Dataset;
  NNFeedForward<>* NNFF;
  NNStatistics<> Stat;
};

#endif  // DATASETVIEWER_H
