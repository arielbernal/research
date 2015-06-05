#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <functional>
#include <iostream>
#include <../common/nnlayer.h>
#include <../common/nndataset.h>
#include <../common/rapidjson/document.h>
#include <../common/rapidjson/prettywriter.h>
#include <../common/rapidjson/filestream.h>
#include <../common/rapidjson/stringbuffer.h>

struct NNStatistics {
  NNStatistics() : MSE(1.0), Errors(1), N(1) {}
  float MSE;
  size_t Errors;
  size_t N;
  float getAccuracy() { return 1 - Errors / float(N); }
};

const double NNFFLearningRate = 0.1;
const double NNFFMomentum = 0.9;
const size_t NNFFMaxEpochs = 4500;
const size_t NNFFEpochStat = 100;
const double NNFFTrainingAccuracy = 0.9;

template <typename T> class NNFeedForward {
public:
  NNFeedForward(size_t NInput, size_t NHidden, size_t NOutput,
                size_t NHiddenLayers = 1)
      : LearningRate(NNFFLearningRate),
        Momentum(NNFFMomentum),
        MaxEpochs(NNFFMaxEpochs),
        EpochStat(NNFFEpochStat),
        TrainingAccuracy(NNFFTrainingAccuracy) {
    init(NInput, NHidden, NOutput, NHiddenLayers);
  }

  NNFeedForward()
      : LearningRate(NNFFLearningRate),
        Momentum(NNFFMomentum),
        MaxEpochs(NNFFMaxEpochs),
        EpochStat(NNFFEpochStat),
        TrainingAccuracy(NNFFTrainingAccuracy) {}

  ~NNFeedForward() { clear(); }

  void clear() {
    for (auto& e : Layers)
      delete e;
    Layers.clear();
  }

  void init(size_t NInput, size_t NHidden, size_t NOutput,
            size_t NHiddenLayers = 1) {
    clear();

    Input = new NNLayer(NInput);
    Layers.push_back(Input);
    for (size_t i = 0; i < NHiddenLayers; ++i)
      Layers.push_back(new NNLayer(NHidden, Layers.back(), NNLayer::HIDDEN));
    Output = new NNLayer(NOutput, Layers.back(), NNLayer::OUTPUT);
    Layers.push_back(Output);
  }

  template <typename K, typename S>
  void feedForward(K* input, std::vector<S>& output) {
    Input->set(input);
    for (size_t i = 1; i < Layers.size(); ++i)
      Layers[i]->feedForward();
    Output->get(output);
  }

  void dump() {
    for (auto& e : Layers)
      e->dump();
    std::cout << "-----------------------------" << std::endl;
  }

  template <typename K, typename S> void train(NNDataset<K, S>* Training) {
    std::vector<T> Result(Output->N);
    std::vector<T> Pattern(Output->N);
    size_t epoch = 0;
    while (epoch < MaxEpochs &&
           (TrainingStat.getAccuracy() < TrainingAccuracy)) {
      for (size_t i = 0; i < Training->getN(); ++i) {
        feedForward(Training->getSample(i), Result);
        Training->getLabel(i, Pattern);
        backPropagate(Pattern);
        if (i % 1000 == 0)
          std::cout << "Tr = " << i << std::endl;
      }
      if (epoch % EpochStat == 0) {
        statistics(Training, TrainingStat);
        if (CallbackProgress)
          CallbackProgress(epoch, TrainingStat);
      }
      epoch++;
    }
    if (CallbackProgress)
      CallbackProgress(epoch, TrainingStat);
  }

  template <typename K, typename S>
  void statistics(NNDataset<K, S>* Dataset, NNStatistics& Stat) {
    std::vector<T> Result(Output->N);
    std::vector<T> Pattern(Output->N);
    T mse = 0;
    size_t errors = 0;
    for (size_t i = 0; i < Dataset->getN(); ++i) {
      feedForward(Dataset->getSample(i), Result);
      Dataset->getLabel(i, Pattern);
      mse += MSE(Result, Pattern);
      if (!isSameOutput(Result, Pattern))
        errors++;
    }
    Stat.N = Dataset->getN();
    Stat.MSE = mse / Dataset->getN();
    Stat.Errors = errors;
  }

  void setCallbackProgress(std::function<void(size_t, NNStatistics&)> Func) {
    CallbackProgress = Func;
  }

  void setLearningRate(double rate) { LearningRate = rate; }
  void setMomentum(double m) { Momentum = m; }
  void setMaxEpochs(size_t n) { MaxEpochs = n; }
  void setEpochStat(size_t n) { EpochStat = n; }
  void setTrainingAccuracy(double accuracy) { TrainingAccuracy = accuracy; }

  bool save(const std::string& Filename) {

//    rapidjson::Document d;
//    d.SetObject();
//    d.AddMember("NInput", Input->N, d.GetAllocator());
//    d.AddMember("NHidden", Layers[1]->N, d.GetAllocator());
//    d.AddMember("NOutput", Output->N, d.GetAllocator());
//    d.AddMember("NHiddenLayers", Layers.size() - 2, d.GetAllocator());

//    rapidjson::Value LayersGroup("Layers", Layers.size() - 1);
//    d.AddMember(LayersGroup, d.GetAllocator());
//    for (size_t i = 1; i < Layers.size(); ++i) {
//      rapidjson::Value Layer("Layer", i);
//      LayersGroup.AddMember(Layer,d.GetAllocator());
//      for (size_t j = 0; j < Layers[i]->W.size(); ++j) {
//        for (size_t k = 0; k < Layers[i]->W[j].size(); ++k) {
//          std::cout << "i, j, k = " << i << " " << j << " " << k << " "
//                    << Layers[i]->W[j][k] << std::endl;
//        }
//      }
//    }


    std::ofstream ofj("Test.json");
    rapidjson::GenericStringBuffer<rapidjson::UTF8<> > buffer;
    rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > >
        writer(buffer);
    writer.StartObject();
    writer.StartArray();
    writer.EndArray();
    writer.EndObject();


    ofj << buffer.GetString();
    ofj.close();

    return true;
  }

protected:
  template <typename K> void backPropagate(const std::vector<K>& Pattern) {
    Output->computeDeltas(Pattern);
    for (size_t i = Layers.size() - 2; i > 0; i--)
      Layers[i]->computeDeltas();
    for (size_t i = 1; i < Layers.size(); i++)
      Layers[i]->updateWeights(LearningRate, Momentum);
  }

  template <typename K>
  T MSE(const std::vector<K>& Yp, const std::vector<K>& Y) {
    T mse = 0;
    for (size_t i = 0; i < Yp.size(); ++i) {
      T d = Yp[i] - Y[i];
      mse += d * d;
    }
    return mse / Yp.size();
  }

  T roundedOutput(T v) {
    if (v >= 0.9)
      return 1;
    if (v <= 0.1)
      return 0;
    return -1;
  }

  template <typename K>
  bool isSameOutput(const std::vector<K>& Output,
                    const std::vector<K>& Pattern) {
    for (size_t i = 0; i < Output.size(); ++i)
      if (Pattern[i] != roundedOutput(Output[i]))
        return false;
    return true;
  }

private:
  double LearningRate;
  double Momentum;
  size_t MaxEpochs;
  size_t EpochStat;
  double TrainingAccuracy;

  std::vector<NNLayer*> Layers;
  NNLayer* Input;
  NNLayer* Output;
  std::function<void(size_t, NNStatistics&)> CallbackProgress;
  NNStatistics TrainingStat;
};

#endif // NNCLASS
