#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <nndataset.h>

struct NNLayer {
  NNLayer(size_t N) : N(N), Neurons(N), Prev(0) {}

  NNLayer(size_t N, NNLayer *Prev)
      : N(N), Neurons(N), Bias(N), W(N), Prev(Prev) {
    for (size_t i = 0; i < N; ++i) {
      float *p = new float[Prev->N];
      memset(p, 0, Prev->N * sizeof(float));
      W[i] = p;
    }
  }

  ~NNLayer() {
    for (auto &e : W)
      delete e;
  }

  template <typename T> void set(T *input) {
    for (size_t i = 0; i < N; ++i)
      Neurons[i] = input[i];
  }

  template <typename T> void get(T *output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = Neurons[i];
  }

  void update() {
    for (size_t i = 0; i < N; ++i) {
      float netj = fPropagation(Prev->Neurons, W[i]);
      Neurons[i] = fActivation(netj, Bias[i]);
    }
  }

  float fPropagation(const std::vector<float> &Inputs, float *Weights) {
    float netj = 0;
    for (size_t i = 0; i < Prev->N; ++i) {
      netj += Inputs[i] * Weights[i];
    }
    return netj;
  }

  float fActivation(float Netj, float bias) {
    float v = Netj - bias;
    return 1 / (1 + exp(-v));
  }

  void randomWeights() {
    for (size_t i = 0; i < N; ++i) {
      float *pW = W[i];
      for (size_t j = 0; j < Prev->N; ++j)
        pW[j] = float(rand()) / RAND_MAX - 0.5f;
    }
  }

  size_t N;
  std::vector<float> Neurons;
  std::vector<float> Bias;
  std::vector<float *> W;
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
      Layers[i]->update();
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
        //backPropagate(OutputLabel);
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
