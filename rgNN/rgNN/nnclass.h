#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <nndataset.h>

struct NNLayer {
  enum { INPUT, HIDDEN, OUTPUT };

  NNLayer(size_t N)
      : N(N), A(N + 1), delta(N + 1), Prev(0), Next(0), Type(INPUT) {}

  NNLayer(size_t N, NNLayer *Prev, size_t Type)
      : N(N), A(N + 1), W(N + 1, std::vector<float>(Prev->N + 1)), delta(N + 1),
        Prev(Prev), Next(0), Type(Type) {
    Prev->Next = this;
    setRandomWeights();
    A[N] = 1;
  }

  template <typename T> void set(T *input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = input[i];
  }

  template <typename T> void get(T *output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  void feedForward() {
    for (size_t k = 0; k < N; ++k) {
      float Z = weightedSum(Prev->A, W[k]);
      A[k] = g(Z);
    }
  }

  float weightedSum(const std::vector<float> &Inputs,
                    const std::vector<float> &Weights) {
    float S = 0;
    for (size_t j = 0; j < Prev->N + 1; ++j) {
      S += Inputs[j] * Weights[j];
    }
    return S;
  }

  float g(float x) { return 1 / (1 + exp(-x)); }

  void setRandomWeights() {
    for (size_t i = 0; i < N + 1; ++i) {
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[i][j] = float(rand()) / RAND_MAX - 0.5f;
    }
  }

  void computeDeltas(float *t) {
    if (Type == OUTPUT) {
      for (size_t k = 0; k < N + 1; ++k)
        delta[k] = (A[k] - t[k]) * A[k] * (1 - A[k]);
    }
  }
  void computeDeltas() {
    if (Type == HIDDEN) {
      for (size_t j = 0; j < N + 1; ++j) {
        float S = 0;
        for (size_t k = 0; k < Next->N + 1; ++k)
          S += Next->delta[k] * Next->W[k][j];
        delta[j] = A[j] * (1 - A[j]) * S;
      }
    }
  }

  void updateWeights(float eta) {
    if (Type == HIDDEN || Type == OUTPUT) {
      for (size_t k = 0; k < N + 1; ++k) {
        for (size_t j = 0; j < Prev->N + 1; ++j)
          W[k][j] = -eta * delta[k] * Prev->A[j];
      }
    }
  }

  size_t N;
  std::vector<float> A;
  std::vector<std::vector<float> > W;
  std::vector<float> delta;
  NNLayer *Prev;
  NNLayer *Next;
  size_t Type;
};

class NNFeedForward {
public:
  NNFeedForward() {}
  NNFeedForward(size_t NInput, size_t NHidden, size_t NHiddenLayers,
                size_t NOutput) {
    init(NInput, NHidden, NHiddenLayers, NOutput);
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

    Layers.push_back(new NNLayer(NInput));
    for (size_t i = 0; i < NHiddenLayers; ++i)
      Layers.push_back(new NNLayer(NHidden, Layers.back(), NNLayer::HIDDEN));
    Layers.push_back(new NNLayer(NOutput, Layers.back(), NNLayer::OUTPUT));
  }

  template <typename T, typename S> void feedForward(T *input, S *output) {
    Layers[0]->set(input);
    for (size_t i = 1; i < Layers.size(); ++i) {
      Layers[i]->feedForward();
    }
    Layers.back()->get(output);
  }

  void backPropagate(float *OutputLabel) {
    int NOut = Layers.size() - 1;
    Layers[NOut]->computeDeltas(OutputLabel);
    for (int i = NOut - 1; i > 0; i--) {
      Layers[i]->computeDeltas();
    }
    for (int i = 1; i <= NOut; i++) {
      Layers[i]->updateWeights(0.01);
    }
  }

  void train(NNDataset *Training, size_t MaxEpochs) {
    for (size_t k = 0; k < MaxEpochs; ++k) {
      // for (size_t i = 0; i < Training->getN() / 1000 ; ++i) {
      for (size_t i = 0; i < 1; ++i) {
        float Output[10];
        float OutputLabel[10];
        for (int h = 0; h < 10; ++h) {
          feedForward(Training->getSample(i), Output);
          labelToOutput(Training->getLabel(i), OutputLabel);
          std::cout << "---------------------------------" << std::endl;
          std::cout << "I = " << i << " Label = " << (int)Training->getLabel(i)
                    << std::endl;
          for (int j = 0; j < 10; ++j)
            std::cout << Output[j] << " ";
          std::cout << std::endl;

          backPropagate(OutputLabel);
          feedForward(Training->getSample(i), Output);
          for (int j = 0; j < 10; ++j)
            std::cout << Output[j] << " ";
          std::cout << std::endl;
        }

        // std::cout << "Training i = " << i << std::endl;
      }
      float mse = MSE(Training);
      std::cout << "MSE = " << mse << std::endl;
    }
  }

protected:
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

  float MSE(NNDataset *Dataset) {
    float mse = 0;
    for (size_t i = 0; i < Dataset->getN() / 1000; ++i) {
      float Output[10];
      float OutputLabel[10];
      feedForward(Dataset->getSample(i), Output);
      labelToOutput(Dataset->getLabel(i), OutputLabel);
      mse += MSE(Output, OutputLabel, 10);
    }
    return mse / Dataset->getN();
  }

private:
  std::vector<NNLayer *> Layers;
};

#endif // NNCLASS
