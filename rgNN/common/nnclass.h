#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include <../common/nnlayer.h>
#include <../common/nndataset.h>
#include <../common/rapidjson/document.h>
#include <../common/rapidjson/prettywriter.h>
#include <../common/rapidjson/filestream.h>
#include <../common/rapidjson/stringbuffer.h>
#include <../common/utilities/rgScopedTimer.h>

template <typename T = double>
struct NNStatistics {
  NNStatistics() : MSE(1.0), Errors(1), N(1) {}
  T MSE;
  size_t Errors;
  size_t N;
  T getAccuracy() { return 1 - Errors / float(N); }
  std::vector<size_t> ErrorIds;
};

const double NNFFLearningRate = 0.1;
const double NNFFMomentum = 0.9;
const size_t NNFFMaxEpochs = 4500;
const size_t NNFFEpochStat = 100;
const double NNFFTrainingAccuracy = 0.9;

template <typename T = double>
class NNFeedForward {
 public:
  NNFeedForward(size_t NInput,
                size_t NHidden,
                size_t NOutput,
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

  void init(size_t NInput,
            size_t NHidden,
            size_t NOutput,
            size_t NHiddenLayers = 1) {
    clear();

    Input = new NNLayer<T>(NInput);
    Layers.push_back(Input);
    for (size_t i = 0; i < NHiddenLayers; ++i)
      Layers.push_back(new NNLayer<T>(NHidden, Layers.back()));
    Output = new NNLayer<T>(NOutput, Layers.back());
    Layers.push_back(Output);
    OutputSize = NOutput;
    StopTraining = false;
  }

  void feedForward(T* input, T* output) {
    Input->set(input);
    for (size_t i = 1; i < Layers.size(); ++i)
      Layers[i]->feedForward();
    Output->get(output);
  }

  void stopTraining() { StopTraining = true; }

  template <typename S>
  void train(NNDataset<T, S>* Training) {
    StopTraining = false;
    std::vector<T> Result(OutputSize);
    size_t epoch = 0;
    while (epoch < MaxEpochs &&
           (TrainingStat.getAccuracy() < TrainingAccuracy) && !StopTraining) {
      //Training->sortByMSE();
      Training->randomizeOrder();
      for (auto& e : *Training) {
        if (StopTraining)
          break;
        feedForward(e->Input, Result.data());
        e->MSE = MSE(Result.data(), e->Output);
        backPropagate(e->Output);
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

  static size_t getLabel(std::vector<T>& Result) {
    T vmax = Result[0];
    size_t imax = 0;
    for (size_t i = 0; i < Result.size(); ++i) {
      if (Result[i] > vmax) {
        vmax = Result[i];
        imax = i;
      }
    }
    return imax;
  }

  template <typename S>
  void statistics(NNDataset<T, S>* Dataset, NNStatistics<T>& Stat) {
    Stat.ErrorIds.clear();
    std::vector<T> Result(OutputSize);
    T mse = 0;
    size_t errors = 0;
    for (auto& e : *Dataset) {
      feedForward(e->Input, Result.data());
      e->MSE = MSE(Result.data(), e->Output);
      mse += e->MSE;
      e->Error = false;
      if (getLabel(Result) != e->Label) {
        errors++;
        Stat.ErrorIds.push_back(e->Id);
        e->Error = true;
      }
    }
    Stat.N = Dataset->getN();
    Stat.MSE = mse / Dataset->getN();
    Stat.Errors = errors;
  }

  void setCallbackProgress(std::function<void(size_t, NNStatistics<T>&)> Func) {
    CallbackProgress = Func;
  }

  void setLearningRate(double rate) { LearningRate = rate; }
  void setMomentum(double m) { Momentum = m; }
  void setMaxEpochs(size_t n) { MaxEpochs = n; }
  void setEpochStat(size_t n) { EpochStat = n; }
  void setTrainingAccuracy(double accuracy) { TrainingAccuracy = accuracy; }

  double getLearningRate() { return LearningRate; }

  size_t getNInput() { return Input->N; }
  size_t getNHidden() { return Layers[1]->N; }
  size_t getNOutput() { return Output->N; }
  size_t getNHiddenLayers() { return Layers.size() - 2; }

  bool save(const std::string& Filename) {
    std::ofstream ofs(Filename.c_str());
    if (!ofs.is_open()) {
      std::cout << "Error saving to file : " << Filename << std::endl;
      return false;
    }
    rapidjson::GenericStringBuffer<rapidjson::UTF8<> > buffer;
    rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > >
        writer(buffer);
    writer.StartObject();
    writer.String("NInput");
    writer.Int64(getNInput());
    writer.String("NHidden");
    writer.Int64(getNHidden());
    writer.String("NOutput");
    writer.Int64(getNOutput());
    writer.String("NHiddenLayers");
    writer.Int64(getNHiddenLayers());
    writer.String("Weights");
    writer.StartArray();
    for (size_t i = 1; i < Layers.size(); ++i) {
      for (size_t j = 0; j < Layers[i]->W.size(); ++j) {
        for (size_t k = 0; k < Layers[i]->W[j].size(); ++k) {
          writer.Double(Layers[i]->W[j][k]);
        }
      }
    }
    writer.EndArray();
    writer.EndObject();
    ofs << buffer.GetString();
    ofs.close();
    return true;
  }

  bool load(const std::string& Filename) {
    std::ifstream ifs(Filename.c_str());
    if (!ifs.is_open()) {
      std::cout << "Error file not found : " << Filename << std::endl;
      return false;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();
    rapidjson::Document d;
    if (d.Parse<0>(buffer.str().c_str()).HasParseError()) {
      std::cout << "Error parsing json file : " << Filename << std::endl;
      return false;
    }
    size_t NInput = d["NInput"].GetInt64();
    size_t NHidden = d["NHidden"].GetInt64();
    size_t NOutput = d["NOutput"].GetInt64();
    size_t NHiddenLayers = d["NHiddenLayers"].GetInt64();
    init(NInput, NHidden, NOutput, NHiddenLayers);
    const rapidjson::Value& L = d["Weights"];
    size_t h = 0;
    for (size_t i = 1; i < Layers.size(); ++i) {
      for (size_t j = 0; j < Layers[i]->W.size(); ++j) {
        for (size_t k = 0; k < Layers[i]->W[j].size(); ++k) {
          Layers[i]->W[j][k] = L[h].GetDouble();
          h++;
        }
      }
    }
    return true;
  }

 protected:
  void backPropagate(const T* Pattern) {
    Output->computeDeltas(Pattern);
    for (size_t i = Layers.size() - 2; i > 0; i--)
      Layers[i]->computeDeltas();
    for (size_t i = 1; i < Layers.size(); i++)
      Layers[i]->updateWeights(LearningRate, Momentum);
  }

  T MSE(const T* Yp, const T* Y) {
    T mse = 0;
    for (size_t i = 0; i < OutputSize; ++i) {
      T d = Yp[i] - Y[i];
      mse += d * d;
    }
    return mse / T(OutputSize);
  }

  T roundedOutput(T v) {
    if (v >= 0.8)
      return 1;
    if (v <= -0.8)
      return -1;
    return 0;
  }

  bool isSameOutput(const T* Output, const T* Pattern) {
    for (size_t i = 0; i < OutputSize; ++i)
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
  bool StopTraining;

  std::vector<NNLayer<T>*> Layers;
  NNLayer<T>* Input;
  NNLayer<T>* Output;
  size_t OutputSize;
  std::function<void(size_t, NNStatistics<T>&)> CallbackProgress;
  NNStatistics<T> TrainingStat;
};

#endif  // NNCLASS
