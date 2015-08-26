#ifndef FFNN3L_H
#define FFNN3L_H

#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include "nndataset.h"

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
        W1(NO, std::vector<double>(NH + 1)),
        DW0(NH, std::vector<double>(NI + 1)),
        DW1(NO, std::vector<double>(NH + 1)) {
    Input[NI] = -1;
    Hidden[NH] = -1;
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
      Output[k] = Z;
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
      for (size_t j = 0; j <= NI; ++j) W0[i][j] = distribution0(generator);

    double sigma1 = 1 / sqrt(NH + 1);
    std::normal_distribution<double> distribution1(0, sigma1);
    for (size_t i = 0; i < NO; ++i)
      for (size_t j = 0; j <= NH; ++j) W1[i][j] = distribution1(generator);
  }

  std::vector<std::vector<double>>& getW0() { return W0; }
  std::vector<std::vector<double>>& getW1() { return W1; }

  void clear() {
    Input.clear();
    Hidden.clear();
    Output.clear();
    W0.clear();
    W1.clear();
  }

  void save(const std::string& Filename) {
    std::ofstream ofs(Filename.c_str());
    if (!ofs.is_open()) {
      std::cout << "Error saving to file : " << Filename << std::endl;
      return;
    }
    ofs << NI << " " << NH << " " << NO << std::endl;
    for (size_t i = 0; i < NH; ++i)
      for (size_t j = 0; j <= NI; ++j) ofs << W0[i][j] << "\n";
    for (size_t i = 0; i < NO; ++i)
      for (size_t j = 0; j <= NH; ++j) ofs << W1[i][j] << "\n";

    ofs.close();
  }

  void load(const std::string& Filename) {
    std::ifstream ifs(Filename.c_str());
    if (!ifs.is_open()) {
      std::cout << "Error loading file : " << Filename << std::endl;
      return;
    }
    ifs >> NI >> NH >> NO;
    std::cout << "FFNN3L(" << NI << ", " << NH << ", " << NO << ")"
              << std::endl;
    Input.resize(NI + 1);
    Hidden.resize(NH + 1);
    Output.resize(NO);
    W0.resize(NH, std::vector<double>(NI + 1));
    W1.resize(NO, std::vector<double>(NH + 1));
    DW0.resize(NH, std::vector<double>(NI + 1));
    DW1.resize(NO, std::vector<double>(NH + 1));
    for (size_t i = 0; i < NH; ++i)
      for (size_t j = 0; j <= NI; ++j) ifs >> W0[i][j];
    for (size_t i = 0; i < NO; ++i)
      for (size_t j = 0; j <= NH; ++j) ifs >> W1[i][j];
    ifs.close();
  }

  void train(NNDataset<double>& Training, size_t MaxEpochs, double eta = 0.09,
             double mu = 0.5) {
    for (auto& e : DW0)  for (auto &v : e)    v = 0;
    for (auto& e : DW1)  for (auto &v : e)    v = 0;
    std::vector<double> Result(NO);
    size_t epoch = 0;
    std::cout << Training.size() << std::endl;
    while (epoch < MaxEpochs) {
      double MSETotal = 0;
      for (auto& e : Training.getSamples()) {
        feedForward(e->Input, Result);
        MSETotal += MSE(Result, e->Output);
        backPropagate(e->Output, eta, mu);
      }
      std::cout << "Epoch = " << epoch
                << "  Training MSETotal = " << MSETotal / Training.size() << std::endl;
      epoch++;
    }
  }

  void test(NNDataset<double>& Test) {
    double MSETotal = 0;
    std::vector<double> Result(NO);
    for (auto& e : Test.getSamples()) {
      feedForward(e->Input, Result);
      MSETotal += MSE(Result, e->Output);
    }
    std::cout << "Test MSETotal = " << MSETotal / Test.size() << std::endl;
  }

 protected:
  double MSE(const std::vector<double>& a, const std::vector<double>& b) {
    double S = 0;
    for (size_t i = 0; i < a.size(); ++i) {
      double dx = a[i] - b[i];
      S += dx * dx;
    }
    return S / 2;
  }

  void backPropagate(const std::vector<double>& t, double eta, double mu) {
    for (size_t k = 0; k < NO; ++k) {
      double dk = (Output[k] - t[k]) * DSIGMOID(Output[k]);
      for (size_t j = 0; j <= NH; ++j)
        DW1[k][j] = -eta * dk * Hidden[j] + mu * DW1[k][j];
    }
    for (size_t j = 0; j < NH; ++j) {
      double S = 0;
      for (size_t k = 0; k < NO; ++k)
        S += (Output[k] - t[k]) * DSIGMOID(Output[k]) * W1[k][j];
      // std::cout << "H = " << Hidden[j] << " DS = " << DSIGMOID(Output[j])
      //           << std::endl;
      double dj = S * DSIGMOID(Hidden[j]);
      for (size_t i = 0; i <= NI; ++i)
        DW0[j][i] = -eta * dj * Input[i] + mu * DW0[i][j];
    }
    for (size_t k = 0; k < NO; ++k)
      for (size_t j = 0; j <= NI; ++j) W1[k][j] += DW1[k][j];
    for (size_t j = 0; j < NH; ++j)
      for (size_t i = 0; i <= NI; ++i) W0[j][i] += DW0[j][i];
  }

 private:
  size_t NI, NH, NO;
  std::vector<double> Input;
  std::vector<double> Hidden;
  std::vector<double> Output;
  std::vector<std::vector<double>> W0;
  std::vector<std::vector<double>> W1;
  std::vector<std::vector<double>> DW0;
  std::vector<std::vector<double>> DW1;
};

#endif  // FFNN3L_H
