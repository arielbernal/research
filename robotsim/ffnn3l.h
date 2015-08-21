#ifndef FFNN3L_H
#define FFNN3L_H

#include <vector>
#include <functional>
#include <iostream>
#include <random>

#define SIGMOID_A (1.715904709)
#define SIGMOID_B (0.6666666667)
#define SIGMOID_A2 (SIGMOID_A * SIGMOID_A)
#define SIGMOID_BA (SIGMOID_B / SIGMOID_A)
#define DSIGMOID(S) (SIGMOID_BA * (SIGMOID_A2 - S * S))
#define SIGMOID(x) (SIGMOID_A * tanh(SIGMOID_B * x))
//#define SIGMOID(x) (tanh(x))

class FFNN3L {
 public:
  FFNN3L(size_t NI, size_t NH, size_t NO)
      : NI(NI),
        NH(NH),
        NO(NO),
        Input(NI + 1),
        Hidden(NH + 1),
        Output(NO),
        W0(NH, std::vector<double>(NI + 1)),
        W1(NO, std::vector<double>(NH + 1)) {
    Input[NI] = -1;
    Hidden[NI] = -1;
    setRandomWeights();
  }

  void feedForward(const std::vector<double>& input, std::vector<double>& out) {
    for (size_t i = 0; i < NI; ++i) Input[i] = input[i];
    for (size_t j = 0; j < NH; ++j) {
      double Z = weightedSum(Input, W0[j]);
      Hidden[j] = SIGMOID(Z);
    }
    for (size_t k = 0; k < NO; ++k) {
      double Z = weightedSum(Hidden, W1[k]);
      Output[k] = SIGMOID(Z);
      out[k] = Output[k];
    }
  }

  void getOutput(std::vector<double>& out) {
    for (size_t i = 0; i < NO; ++i) {
      out[i] = Output[i];
    }
  }

  double weightedSum(const std::vector<double>& X,
                     const std::vector<double>& W) {
    double S = 0;
    for (size_t i = 0; i < X.size(); ++i) S += X[i] * W[i];
    return S;
  }

  void setRandomWeights() {
    static std::default_random_engine generator;

    double sigma0 = 1 / sqrt(NI + 1);
    std::normal_distribution<double> distribution0(0, sigma0);
    for (size_t i = 0; i < NH; ++i)
      for (size_t j = 0; j < NI; ++j) W0[i][j] = distribution0(generator);

    double sigma1 = 1 / sqrt(NH + 1);
    std::normal_distribution<double> distribution1(0, sigma1);
    for (size_t i = 0; i < NO; ++i)
      for (size_t j = 0; j < NH; ++j) W1[i][j] = distribution1(generator);
  }

  std::vector<std::vector<double>>& getW0() { return W0; }
  std::vector<std::vector<double>>& getW1() { return W1; }

 private:
  size_t NI, NH, NO;
  std::vector<double> Input;
  std::vector<double> Hidden;
  std::vector<double> Output;
  std::vector<std::vector<double>> W0;
  std::vector<std::vector<double>> W1;
};

#endif  // FFNN3L_H
