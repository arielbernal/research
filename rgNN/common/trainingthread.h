#ifndef TRAININGTHREAD
#define TRAININGTHREAD

#include <QThread>
#include <../common/nnclass.h>

template <typename T, typename K>
class TrainingThread : public QThread {
 public:
  enum { STOPPED, RUNNING };
  TrainingThread(NNFeedForward<T>* nnff,
                                 NNDataset<T, K>* Training)
      : nnff(nnff), Training(Training), Status(STOPPED) {
  }

  void stopTraining() { nnff->stopTraining(); }

  bool isRunning() { return Stauts == RUNNING; }
  bool isStopped() { return Status == STOPPED; }

 private:
  QMutex m_mutex;

  void run() {
    Status = RUNNING;
    nnff->train(Training);
    Status = STOPPED;
  }

  NNFeedForward<T>* nnff;
  NNDataset<T, K>* Training;
  size_t Status;
};

#endif  // TRAININGTHREAD
