#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <functional>
#include <iostream>
#include <../common/nnlayer.h>
#include <../common/nndataset.h>

class NNFeedForward {
public:
  NNFeedForward() {}
  NNFeedForward(size_t NInput, size_t NHidden, size_t NHiddenLayers,
                size_t NOutput) {
    init(NInput, NHidden, NHiddenLayers, NOutput);
  }
  void clear() {
    for (auto& e : Layers)
      delete e;
    Layers.clear();
  }

  void init(size_t NInput, size_t NHidden, size_t NHiddenLayers,
            size_t NOutput) {
    clear();

    Input = new NNLayer(NInput);
    Layers.push_back(Input);
    for (size_t i = 0; i < NHiddenLayers; ++i)
      Layers.push_back(new NNLayer(NHidden, Layers.back(), NNLayer::HIDDEN));
    Output = new NNLayer(NOutput, Layers.back(), NNLayer::OUTPUT);
    Layers.push_back(Output);
  }

  template <typename T, typename S>
  void feedForward(T* input, std::vector<S>& output) {
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

  template <typename T> void backPropagate(const std::vector<T>& Pattern) {
    Output->computeDeltas(Pattern);
    for (size_t i = Layers.size() - 2; i > 0; i--)
      Layers[i]->computeDeltas();
    for (size_t i = 1; i < Layers.size(); i++)
      Layers[i]->updateWeights(0.05f);
  }

  template <typename T>
  void labelToPattern(uint8_t label, std::vector<T>& pattern) {
    for (size_t i = 0; i < pattern.size(); ++i) {
      if (i == label)
        pattern[i] = 1;
      else
        pattern[i] = 0;
    }
  }

  template <typename T, typename S>
  void train(NNDataset<T, S>* Training, size_t MaxEpochs = 1) {
    std::vector<float> Output(Training->getSize());
    std::vector<float> Pattern(Training->getSize());
    std::cout << "Epochs = " << MaxEpochs << " N = " << Training->getN()
              << " Size = " << Training->getSize() << std::endl;
    size_t epoch = 0;
    while (epoch < MaxEpochs) {
      for (size_t i = 0; i < Training->getN(); ++i) {
        feedForward(Training->getSample(i), Output);
        labelToPattern(Training->getLabel(i), Pattern);
        backPropagate(Pattern);
      }
      float mse = MSE(Training);
      if (CallbackProgress) {
        CallbackProgress(epoch, mse);
      }
      epoch++;
    }
  }

  template <typename T>
  float MSE(const std::vector<T>& Yp, const std::vector<T>& Y) {
    float mse = 0;
    for (size_t i = 0; i < Yp.size(); ++i) {
      float d = Yp[i] - Y[i];
      mse += d * d;
    }
    return mse / Yp.size();
  }

  template <typename T>
  bool isSameOutput(const std::vector<T>& Output,
                    const std::vector<T>& Pattern) {
    for (size_t i = 0; i < Yp.size(); ++i)
      if (Pattern[i] != roundedOutput(Output[i]))
        return false;
    return true;
  }

  template <typename T, typename S> void stat(NNDataset<T, S>* Training) {
    std::vector<float> Output(Training->getSize());
    std::vector<float> Pattern(Training->getSize());
    float mse = 0;
    size_t errors = 0;
    for (size_t i = 0; i < Training->getN(); ++i) {
      feedForward(Training->getSample(i), Output);
      labelToPattern(Training->getLabel(i), Pattern);
      mse += MSE(Output, Pattern);
      if (!isSameOutput(Output, Pattern)) {
        errors++;
      }
    }
    TrainingMSE = mse / Training->getN();
    TrainingError = 100 - (errors / float(Training->getN()) * 100);
  }

  void setCallbackProgress(std::function<void(size_t, float)> Func) {
    CallbackProgress = Func;
  }

private:
  std::vector<NNLayer*> Layers;
  NNLayer* Input;
  NNLayer* Output;
  std::function<void(size_t, float)> CallbackProgress;
  float TrainingMSE;
  float TrainingError;
};

#endif // NNCLASS
