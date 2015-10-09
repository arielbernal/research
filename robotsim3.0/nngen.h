#ifndef NNGEN_H
#define NNGEN_H

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

struct GENNeuron {
  enum { INPUT, OUTPUT, HIDDEN };
  GENNeuron(size_t nntype, float x, float y, float z)
      : x(x), y(y), z(z), nntype(nntype) {}
  float x, y, z; // position
  size_t nntype;
  std::list<GENNeuron *> input;
};

class GENNeuralNet {
public:
  GENNeuralNet(size_t NInput, size_t NOutput, size_t NHidden = 0,
               float XSize = 1, float YSize = 1, float ZSize = 1)
      : NInput(NInput), NOutput(NOutput), NHidden(NHidden), XSize(XSize),
        YSize(YSize), ZSize(ZSize) {
    initializeRandomNet();
  }

protected:
  void initializeRandomNet() {
    // unsigned seed =
    // std::chrono::system_clock::now().time_since_epoch().count();
    auto uniform =
        std::bind(std::uniform_real_distribution<float>(0, 1), generator);

    for (size_t i = 0; i < NInput; ++i) {
      GENNeuron *Neuron =
          new GENNeuron(GENNeuron::INPUT, uniform(), uniform(), uniform());
      Input.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NOutput; ++i) {
      GENNeuron *Neuron =
          new GENNeuron(GENNeuron::OUTPUT, uniform(), uniform(), uniform());
      Output.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NHidden; ++i) {
      GENNeuron *Neuron =
          new GENNeuron(GENNeuron::HIDDEN, uniform(), uniform(), uniform());
      Hidden.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
  }

  void addHiddenNeuron() {
    NHidden++;
    GENNeuron *Neuron =
        new GENNeuron(GENNeuron::HIDDEN, uniform(), uniform(), uniform());
    Hidden.push_back(Neuron);
    Neurons.push_back(Neuron);
  }


  void addSynapse(size_t i , size_t j) {

  }

private:
  size_t NInput;
  size_t NOutput;
  size_t NHidden;
  float XSize, YSize, ZSize;
  std::vector<GENNeuron *> Input;
  std::vector<GENNeuron *> Output;
  std::vector<GENNeuron *> Hidden;
  std::vector<GENNeuron *> Neurons;
  std::default_random_engine generator;
};

#endif // FFNN3L_H
