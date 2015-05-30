#ifndef NNCLASS
#define NNCLASS

#include <vector>
#include <nndataset.h>

struct NNLayer {
  enum { INPUT, HIDDEN, OUTPUT };

  NNLayer(size_t N) : N(N), A(N + 1), Prev(0), Next(0), Type(INPUT) {
    A[N] = -1;
  }

  NNLayer(size_t N, NNLayer *Prev, size_t Type)
      : N(N), A(N + 1), W(N, std::vector<float>(Prev->N + 1)), delta(N),
        Prev(Prev), Next(0), Type(Type) {
    A[N] = -1;
    setRandomWeights();
    Prev->Next = this;
  }

  template <typename T> void set(T *input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = float(input[i]);
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
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[i][j] = 2 * (float(rand()) / RAND_MAX) - 1.0f;
    }
  }

  void computeDeltas(float *t) {
    for (size_t k = 0; k < N; ++k)
      delta[k] = (A[k] - t[k]) * A[k] * (1 - A[k]);
  }

  void computeDeltas() {
    for (size_t j = 0; j < N; ++j) {
      float S = 0;
      for (size_t k = 0; k < Next->N; ++k)
        S += Next->delta[k] * Next->W[k][j];
      delta[j] = A[j] * (1 - A[j]) * S;
    }
  }

  void updateWeights(float eta) {
    for (size_t k = 0; k < N; ++k)
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[k][j] -= eta * delta[k] * Prev->A[j];
  }

  void dump() {
    if (Type == INPUT) {
      std::cout << "------ INPUT LAYER --------" << std::endl;
      for (size_t i = 0; i < A.size(); ++i)
        printf("%7.4f\n", A[i]);
      std::cout << std::endl;
    }
    if (Type == HIDDEN) {
      std::cout << "------ HIDDEN LAYER --------" << std::endl;
      for (size_t i = 0; i < A.size() - 1; ++i) {
        printf("%7.4f | ", A[i]);
        for (size_t j = 0; j < W[i].size(); ++j)
          printf("%7.4f ", W[i][j]);
        printf("| %7.4f\n", delta[i]);
      }
      printf("%7.4f\n", A.back());
    }
    if (Type == OUTPUT) {
      std::cout << "------ OUTPUT LAYER --------" << std::endl;
      for (size_t i = 0; i < A.size() - 1; ++i) {
        printf("%7.4f | ", A[i]);
        for (size_t j = 0; j < W[i].size(); ++j)
          printf("%7.4f ", W[i][j]);
        printf("| %7.4f\n", delta[i]);
      }
    }
  }

  size_t N;
  std::vector<float> A;
  std::vector<std::vector<float>> W;
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
  void clear() {
    for (auto &e : Layers)
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

  template <typename T, typename S> void feedForward(T *input, S *output) {
    Input->set(input);
    for (size_t i = 1; i < Layers.size(); ++i)
      Layers[i]->feedForward();
    Output->get(output);
  }

  void dump() {
    for (auto &e : Layers)
      e->dump();
    std::cout << "-----------------------------" << std::endl;
  }

  void backPropagate(float *Pattern) {
    Output->computeDeltas(Pattern);
    for (size_t i = Layers.size() - 2; i > 0; i--) {
      Layers[i]->computeDeltas();
    }
    for (size_t i = 1; i < Layers.size(); i++) {
      Layers[i]->updateWeights(0.1);
    }
  }

  void labelToPattern(uint8_t label, float *pattern, size_t Size) {
    for (size_t i = 0; i < Size; ++i) {
      if (i == label)
        pattern[i] = 1;
      else
        pattern[i] = 0;
    }
  }

  template <typename T, typename S>
  void train(NNDataset<T, S> *Training, size_t MaxEpochs = 1) {
    float *Output = new float[Training->getSize()];
    float *Pattern = new float[Training->getSize()];
    std::cout << "Epochs = " << MaxEpochs << " N = " << Training->getN() << " Size = " << Training->getSize() << std::endl;
    for (size_t k = 0; k < MaxEpochs; ++k) {
      for (size_t i = 0; i < 100; ++i) {
          size_t id = rand() % 4;
          feedForward(Training->getSample(id), Output);
          labelToPattern(Training->getLabel(id), Pattern, Training->getSize());
          //          std::cout << "---------------------------------" <<
          //          std::endl;
          //          std::cout << "I = " << i << " Label = " <<
          //          (int)Training->getLabel(i)
          //                    << std::endl;
          //          for (int j = 0; j < Training->getSize(); ++j)
          //            std::cout << Output[j] << " ";
          //          std::cout << std::endl;
          backPropagate(Pattern);
          //          feedForward(Training->getSample(i), Output);
          //          for (int j = 0; j < Training->getSize(); ++j)
          //            std::cout << Output[j] << " ";
          //          std::cout << std::endl;
      }
      //std::cout << "Epoch = " << k << std::endl;
    }
    delete Output;
    delete Pattern;
  }

private:
  std::vector<NNLayer *> Layers;
  NNLayer *Input;
  NNLayer *Output;
};

#endif // NNCLASS
