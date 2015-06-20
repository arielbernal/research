#ifndef NNLAYER_H
#define NNLAYER_H

#include <vector>
#include <functional>
#include <iostream>
#include <random>

#define SIGMOID_A (1.715904709)
#define SIGMOID_B (0.6666666667)
#define SIGMOID_A2 (SIGMOID_A * SIGMOID_A)
#define SIGMOID_BA (SIGMOID_B / SIGMOID_A)
#define DSIGMOID(S) (SIGMOID_BA * (SIGMOID_A2 - S * S))
//#define SIGMOID(x) (SIGMOID_A * tanh(SIGMOID_B * x))
#define SIGMOID(x) (tanh(x))
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
      A[i] = T(input[i]);
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
    for (int k = 0; k < N; ++k) {
      T Z = weightedSum(Prev->A, W[k]);
      A[k] = SIGMOID(Z);
    }
  }

  T weightedSum(const std::vector<T>& Inputs, const std::vector<T>& Weights) {
    T S = 0;
    for (size_t j = 0; j < Prev->N + 1; ++j)
      S += Inputs[j] * Weights[j];
    return S;
  }

  void setRandomWeights() {
    double sigma = 1 / sqrt(Prev->N + 1);
    std::default_random_engine generator;
    std::normal_distribution<T> distribution(0, sigma);

    std::cout << "SIGMA = " << sigma << std::endl;
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Prev->N + 1; ++j)
        W[i][j] = distribution(generator);
  }

  void computeDeltas(const T* t) {
    #pragma omp parallel for
    for (int k = 0; k < N; ++k) {
      delta[k] = (A[k] - t[k]) * DSIGMOID(A[k]);
    }
  }

  void computeDeltas() {
    #pragma omp parallel for
    for (int j = 0; j < N; ++j) {
      T S = 0;
      for (size_t k = 0; k < Next->N; ++k)
        S += Next->delta[k] * Next->W[k][j];
      delta[j] = S * DSIGMOID(A[j]);
    }
  }

  // Use momentum and store DW
  void updateWeights(T eta, T mu) {
    //  eta = 0.0001 * sqrt(T(N));
    #pragma omp parallel for
    for (int k = 0; k < N; ++k)
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
