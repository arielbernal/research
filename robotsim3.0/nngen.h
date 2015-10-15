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

struct GENNeuron;

struct GENSynapse {
  GENSynapse(GENNeuron *Input, double W) : Input(Input), W(W) {}
  GENNeuron *Input;
  double W; // weight
};

struct GENNeuron {
  enum { INPUT, OUTPUT, EXCITATORY, INHIBITORY };
  GENNeuron(size_t id, size_t nntype, float x, float y, float z)
      : id(id), nntype(nntype), x(x), y(y), z(z), alive(true), v(0), theta(0.5),
        Ap(0), Rp(0), H(-0.2), D(0.2) {}

  void addSynapse(GENNeuron *Neuron, double W) {
    Inputs.push_back(GENSynapse(Neuron, W));
  }

  void cleanUpInputs() {
    Inputs.remove_if([](GENSynapse &S) { return !S.Input->alive; });
  }

  void update() {
    Ap = 0;
    for (auto &e : Inputs)
      v += e.W * e.Input->Ap;
    if (v > theta) {
      Ap = 1;
      v = H;
      return;
    }
    if (v > Rp)
      v = v - D < Rp ? Rp : v - D;
    if (v < Rp)
      v = v + D > Rp ? Rp : v + D;
  }

  void updateSynapses() {}

  size_t id;
  size_t nntype;
  float x, y, z; // Position
  bool alive;
  double v;     // Potential
  double theta; // Threshold
  double Ap;    // Action potential
  double Rp;    // Resting potential
  double H;     // Hyperpolarizing afterpotential
  double D;     // Repolarization
  std::list<GENSynapse> Inputs;
};

class GENNeuralNet {
public:
  GENNeuralNet(size_t NInput, size_t NOutput, size_t NExcitatory = 0,
               float XSize = 1, float YSize = 1, float ZSize = 1)
      : NInput(NInput), NOutput(NOutput), NHidden(NExcitatory + NInhibitory),
        NExcitatory(NExcitatory), NInhibitory(NInhibitory), XSize(XSize),
        YSize(YSize), ZSize(ZSize) {
    initializeRandomNet();
  }

protected:
  void initializeRandomNet() {
    // unsigned seed =
    // std::chrono::system_clock::now().time_since_epoch().count();
    auto uniform =
        std::bind(std::uniform_real_distribution<float>(0, 1), generator);

    size_t j = 0;
    for (size_t i = 0; i < NInput; ++i) {
      GENNeuron *Neuron =
          new GENNeuron(j++, GENNeuron::INPUT, uniform(), uniform(), uniform());
      Input.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NOutput; ++i) {
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::OUTPUT, uniform(),
                                        uniform(), uniform());
      Output.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NExcitatory; ++i) {
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::EXCITATORY, uniform(),
                                        uniform(), uniform());
      Hidden.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NInhibitory; ++i) {
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::INHIBITORY, uniform(),
                                        uniform(), uniform());
      Hidden.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
  }

  void addHiddenNeuron(size_t nntype) {
    auto uniform =
        std::bind(std + ::uniform_real_distribution<float>(0, 1), generator);

    NHidden++;
    size_t id = Neurons.size();
    GENNeuron *Neuron =
        new GENNeuron(id, nntype, uniform(), uniform(), uniform());
    Hidden.push_back(Neuron);
    Neurons.push_back(Neuron);
  }

  void addSynapse(size_t src, size_t target, double W) {
    Neurons[target]->addSynapse(Neurons[src], W);
  }

  void feed(const std::vector<double> &In) {
    for (size_t i = 0; i < Input.size(); ++i)
      Input[i]->v = In[i];
    for (auto &e : Hidden)
      e->update();
    for (auto &e : Output)
      e->update();
  }

  void updateSynapses() {}

private:
  size_t NInput;
  size_t NOutput;
  size_t NHidden;
  size_t NExcitatory;
  size_t NInhibitory;
  float XSize, YSize, ZSize;
  std::vector<GENNeuron *> Input;
  std::vector<GENNeuron *> Output;
  std::vector<GENNeuron *> Hidden;
  std::vector<GENNeuron *> Neurons;

  std::default_random_engine generator;
};

#endif // FFNN3L_H
