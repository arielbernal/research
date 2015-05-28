#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <nndataset.h>

struct NNLayer {
  NNLayer(size_t N) : N(N), A(N + 1), delta(N + 1), Prev(0) {}

  NNLayer(size_t N, NNLayer *Prev)
      : N(N), A(N + 1), W(N + 1, std::vector<float>(Prev->N + 1)), delta(N + 1),
        Prev(Prev) {}

  template <typename T> void set(T *input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = input[i];
    A[N] = 1;
  }

  template <typename T> void get(T *output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  void feedForward() {
    for (size_t i = 0; i < N + 1; ++i) {
      float Zj = Sum(Prev->A, W[i]);
      A[i] = g(Zj);
    }
  }

  float Sum(const std::vector<float> &Inputs,
            const std::vector<float> &Weights) {
    float Aj = 0;
    for (size_t i = 0; i < Prev->N + 1; ++i) {
      Aj += Inputs[i] * Weights[i];
    }
    return Aj;
  }

  float g(float x) { return 1 / (1 + exp(-x)); }

  void randomWeights() {
    for (size_t i = 0; i < N + 1; ++i) {
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[i][j] = float(rand()) / RAND_MAX - 0.5f;
    }
  }

  size_t N;
  std::vector<float> A;
  std::vector<std::vector<float>> W;
  std::vector<float> delta;
  NNLayer *Prev;
};

class NNFeedForward {
public:
  NNFeedForward() {}
  NNFeedForward(size_t NInput, size_t NHidden, size_t NHiddenLayers,
                size_t NOutput) {
    addInputLayer(NInput);
    for (size_t i = 0; i < NHiddenLayers; ++i)
      addHiddenLayer(NHidden);
    addHiddenLayer(NOutput);
  }

  ~NNFeedForward() { clear(); }

  void clear() {
    for (auto &e : Layers)
      delete e;
    Layers.clear();
  }

  void init(size_t NInput, size_t NHidden, size_t NHiddenLayers,
            size_t NOutput) {
    clear();
    addInputLayer(NInput);
    for (size_t i = 0; i < NHiddenLayers; ++i)
      addHiddenLayer(NHidden);
    addHiddenLayer(NOutput);
  }

  template <typename T, typename S> void feedForward(T *input, S *output) {
    Layers[0]->set(input);
    for (size_t i = 1; i < Layers.size(); ++i) {
      Layers[i]->feedForward();
    }
    Layers.back()->get(output);
  }

  void train(NNDataset *T, size_t MaxEpochs) {
    Training = T;
    for (size_t i = 0; i < MaxEpochs; ++i) {
      for (size_t i = 0; i < Training->getN(); ++i) {
        float Output[10];
        float OutputLabel[10];
        feedForward(Training->getSample(i), Output);
        labelToOutput(Training->getLabel(i), OutputLabel);
        // backPropagate(OutputLabel);
      }
      float mse = MSE();
      std::cout << "MSE = " << mse << std::endl;
    }
  }

protected:
  void addInputLayer(size_t N) {
    NNLayer *layer = new NNLayer(N);
    Layers.push_back(layer);
  }

  void addHiddenLayer(size_t N) {
    NNLayer *layer = new NNLayer(N, Layers.back());
    layer->randomWeights();
    Layers.push_back(layer);
  }

  float MSE(float *a, float *b, size_t n) {
    float mse = 0;
    for (size_t i = 0; i < n; ++i) {
      float d = a[i] - b[i];
      mse += d * d;
    }
    return mse / n;
  }

  void labelToOutput(uint8_t label, float *output) {
    memset(output, 0, 10 * sizeof(float));
    output[label] = 1;
  }

  float MSE() {
    float mse = 0;
    for (size_t i = 0; i < Training->getN(); ++i) {
      float Output[10];
      float OutputLabel[10];
      feedForward(Training->getSample(i), Output);
      labelToOutput(Training->getLabel(i), OutputLabel);
      mse += MSE(Output, OutputLabel, 10);
    }
    return mse / Training->getN();
  }

private:
  std::vector<NNLayer *> Layers;
  NNDataset *Training;
};

#endif // NNCLASS
