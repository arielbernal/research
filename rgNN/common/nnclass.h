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

template <typename T>
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

  template <typename K, typename S>
  void train(NNDataset<K, S>* Training) {
    std::vector<T> Result(Output->N);
    std::vector<T> Pattern(Output->N);
    size_t epoch = 0;
    while (epoch < MaxEpochs &&
           (TrainingStat.getAccuracy() < TrainingAccuracy)) {
      for (size_t i = 0; i < Training->getN(); ++i) {
        while (true) {
          feedForward(Training->getSample(i), Result);
          Training->getLabel(i, Pattern);
          if (isSameOutput(Result, Pattern))
            break;
          backPropagate(Pattern);
        }
      }
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

void setLearningRate(double rate) {
  LearningRate = rate;
}
void setMomentum(double m) {
  Momentum = m;
}
void setMaxEpochs(size_t n) {
  MaxEpochs = n;
}
void setEpochStat(size_t n) {
  EpochStat = n;
}
void setTrainingAccuracy(double accuracy) {
  TrainingAccuracy = accuracy;
}

size_t getNInput() {
  return Input->N;
}
size_t getNHidden() {
  return Layers[1]->N;
}
size_t getNOutput() {
  return Output->N;
}
size_t getNHiddenLayers() {
  return Layers.size() - 2;
}

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
template <typename K>
void backPropagate(const std::vector<K>& Pattern) {
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
  if (v >= 0.7)
    return 1;
  if (v <= 0.3)
    return 0;
  return -1;
}

template <typename K>
bool isSameOutput(const std::vector<K>& Output, const std::vector<K>& Pattern) {
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
}
;

#endif  // NNCLASS
