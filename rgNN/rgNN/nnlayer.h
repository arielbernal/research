#ifndef NNLAYER_H
#define NNLAYER_H

#include <vector>
#include <functional>
#include <iostream>

struct NNLayer {
  enum { INPUT, HIDDEN, OUTPUT };

  NNLayer(size_t N) : N(N), A(N + 1), Prev(0), Next(0), Type(INPUT) {
    A[N] = -1;
  }

  NNLayer(size_t N, NNLayer* Prev, size_t Type)
      : N(N),
        A(N + 1),
        W(N, std::vector<float>(Prev->N + 1)),
        delta(N),
        Prev(Prev),
        Next(0),
        Type(Type) {
    A[N] = -1;
    setRandomWeights();
    Prev->Next = this;
  }

  template <typename T>
  void set(T* input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = float(input[i]);
  }

  template <typename T>
  void set(const std::vector<T>& input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = float(input[i]);
  }

  template <typename T>
  void get(T* output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  template <typename T>
  void get(std::vector<T>& output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  void feedForward() {
    for (size_t k = 0; k < N; ++k) {
      float Z = weightedSum(Prev->A, W[k]);
      A[k] = g(Z);
    }
  }

  float weightedSum(const std::vector<float>& Inputs,
                    const std::vector<float>& Weights) {
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

  template <typename T>
  void computeDeltas(const std::vector<T>& t) {
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
  std::vector<std::vector<float> > W;
  std::vector<float> delta;
  NNLayer* Prev;
  NNLayer* Next;
  size_t Type;
};

#endif // NNLAYER_H

