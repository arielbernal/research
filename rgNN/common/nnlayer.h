#ifndef NNLAYER_H
#define NNLAYER_H

#include <vector>
#include <functional>
#include <iostream>

//#define SIGMOID(x) (1.7159*tanh(0.66666667*x))
#define SIGMOID(x) (tanh(x))
#define DSIGMOID(S) (0.66666667 / 1.7159 * (1.7159 + (S)) * (1.7159 - (S)))

template <typename T>
struct NNLayer {
  NNLayer(size_t N) : N(N), A(N + 1), Prev(0), Next(0) { A[N] = -1; }

  NNLayer(size_t N, NNLayer<T>* Prev)
      : N(N),
        A(N + 1),
        W(N, std::vector<T>(Prev->N + 1)),
        DW(N, std::vector<T>(Prev->N + 1)),
        delta(N),
        Prev(Prev),
        Next(0) {
    A[N] = -1;
    setRandomWeights();
    Prev->Next = this;
  }

  void set(T* input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = float(input[i]);
  }

  void set(const std::vector<T>& input) {
    for (size_t i = 0; i < N; ++i)
      A[i] = input[i];
  }

  void get(T* output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  void get(std::vector<T>& output) {
    for (size_t i = 0; i < N; ++i)
      output[i] = A[i];
  }

  void feedForward() {
#pragma omp parallel for
    for (size_t k = 0; k < N; ++k) {
      T Z = weightedSum(Prev->A, W[k]);
      A[k] = SIGMOID(Z);
    }
  }

  float weightedSum(const std::vector<T>& Inputs,
                    const std::vector<T>& Weights) {
    float S = 0;
    for (size_t j = 0; j < Prev->N + 1; ++j) {
      S += Inputs[j] * Weights[j];
    }
    return S;
  }

  // T g(T x) { return 1.7159 * tanh(0.66666667 * x); }
  float g(float x) { return tanh(x); }
  T gp(T x) { return 0.66666667 / 1.7159 * (1.7159 + x) * (1.7159 - x); }

  void setRandomWeights() {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[i][j] = 0.002 * (float(rand()) / RAND_MAX) - 0.001f;
    }
  }

  void computeDeltas(const T* t) {
#pragma omp parallel for
    for (size_t k = 0; k < N; ++k)
      delta[k] = (A[k] - t[k]) * DSIGMOID(A[k]);
  }

  void computeDeltas() {
#pragma omp parallel for
    for (size_t j = 0; j < N; ++j) {
      float S = 0;
      for (size_t k = 0; k < Next->N; ++k)
        S += Next->delta[k] * Next->W[k][j];
      delta[j] = DSIGMOID(A[j]) * S;
    }
  }

  // Use momentum and store DW
  void updateWeights(T eta, T mu) {
#pragma omp parallel for
    for (size_t k = 0; k < N; ++k)
      for (size_t j = 0; j < Prev->N + 1; ++j) {
        T dw = -eta * delta[k] * Prev->A[j] + mu * DW[k][j];
        W[k][j] += dw;
        DW[k][j] = dw;
      }
  }

  size_t N;
  std::vector<T> A;
  std::vector<std::vector<T> > W;
  std::vector<std::vector<T> > DW;
  std::vector<T> delta;
  NNLayer<T>* Prev;
  NNLayer<T>* Next;
};

#endif  // NNLAYER_H
