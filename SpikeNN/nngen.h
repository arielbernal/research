#ifndef NNGEN_H
#define NNGEN_H

#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <list>
#include <map>
#include <chrono>
#include "nndataset.h"
#include "nngenneuron.h"

class GEN1DTest {
public:
  GEN1DTest() {}

  void generateData(size_t n, size_t nb) {
    static std::uniform_int_distribution<size_t> uniform(0, std::pow(2.0f, nb) - 1);
    In.clear();
    Out.clear();
    for (size_t i = 0; i < 10; ++i) {
      size_t id = uniform(generator);
      In.push_back(id);
      if (id >= 4 && id <= 6)
        Out.push_back(1);
      else
        Out.push_back(0);
    }
    generateSpikes(nb);
  }

  void generateSpikes(size_t nb) {
    clearSpikeQueues();
    for (auto &e : In)
      for (size_t i = 0; i < nb; ++i) {
        int cb = int(e) & int(std::pow(2.0f, nb - i - 1.0f));
        SpikesIn.push(cb);
      }
    for (auto &e : Out)
      for (size_t i = 0; i < nb; ++i) {
        int cb = int(e) & int(std::pow(2.0f, nb - i - 1.0f));
        SpikesOut.push(cb);
      }
  }

  void clearSpikeQueues() {
    while (!SpikesIn.empty()) SpikesIn.pop();
    while (!SpikesOut.empty()) SpikesOut.pop();
  }

  std::vector<float> In;
  std::vector<float> Out;
  std::queue<float> SpikesIn;
  std::queue<float> SpikesOut;
  std::default_random_engine generator;
};

class GENNeuralNet {
public:
  GENNeuralNet(size_t NInput, size_t NOutput, size_t NExcitatory = 0,
               size_t NInhibitory = 0, float XSize = 1, float YSize = 1,
               float ZSize = 1)
      : NInput(NInput), NOutput(NOutput), NHidden(NExcitatory + NInhibitory),
        NExcitatory(NExcitatory), NInhibitory(NInhibitory), XSize(XSize),
        YSize(YSize), ZSize(ZSize) {
    initializeRandomNet();
  }

  ~GENNeuralNet() {
    for (auto e : Neurons)
      delete e;
  }

  void dump() {
    for (auto &e : Neurons) {
      e->print();
    }
  }

  std::vector<GENNeuron *> &getNeurons() { return Neurons; }
  std::vector<GENNeuron *> &getInputs() { return Input; }
  std::vector<GENNeuron *> &getOutputs() { return Output; }
  std::vector<GENNeuron *> &getHidden() { return Hidden; }

  void setInput(std::queue<float> &Q) {
    for (auto &e : Input) {
      if (!Q.empty()) {
        e->Ap = Q.front();
        std::cout << "Set Input " << e->Ap << std::endl;
        Q.pop();
      }
    }
  }

  void feedback(std::queue<float> &Q) {
    for (auto &e : Output) {
      if (!Q.empty()) {
        std::cout << "Output = " << e->Ap << " Test = " << Q.front()
                  << std::endl;
        e->Ap = Q.front();
        Q.pop();
      }
    }

    for (auto &e : Output)
      e->updateSynapses();
    for (auto &e : Hidden)
      e->updateSynapses();
  }

  void update() {
    for (auto &e : Hidden)
      e->update();
    for (auto &e : Output)
      e->update();
  }

  void generateSynapses() {
    for (auto &e : Neurons)
      e->createRandomSynapse(Neurons);
  }

  size_t getNSynapses() {
    size_t s = 0;
    for (auto &e : Neurons)
      s += e->PosSynapses.size();
    return s;
  }

  size_t getNNeurons() { return Neurons.size(); }

  size_t getNInput() { return NInput; }

  size_t getNOutput() { return NOutput; }

  size_t getNExitatory() { return NExcitatory; }

  size_t getNInhibitory() { return NInhibitory; }

protected:
  void uniformSphere(float &x, float &y, float &z, float radius = 1,
                     bool surface = false) {
    static std::normal_distribution<float> normal(0, 1);
    x = normal(generator);
    y = normal(generator);
    z = normal(generator);
    float dnorm = sqrt(x * x + y * y + z * z);
    x = radius * x / dnorm;
    y = radius * y / dnorm;
    z = radius * z / dnorm;
    if (!surface) {
      static std::uniform_real_distribution<float> uniform(0, 1);
      float k = std::pow(uniform(generator), 1.0f / 3.0f);
      x *= k;
      y *= k;
      z *= k;
    }
  }

  void initializeRandomNet() {

    // unsigned seed =
    // std::chrono::system_clock::now().time_since_epoch().count();
    // auto uniform =
    //     std::bind(std::uniform_real_distribution<float>(-1, 1), generator);

    size_t j = 0;
    for (size_t i = 0; i < NInput; ++i) {
      float px, py, pz;
      uniformSphere(px, py, pz, 1, true);
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::INPUT, px, py, pz);
      Input.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NOutput; ++i) {
      float px, py, pz;
      uniformSphere(px, py, pz, 1, true);
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::OUTPUT, px, py, pz);
      Output.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NExcitatory; ++i) {
      float px, py, pz;
      uniformSphere(px, py, pz, 0.98, false);
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::EXCITATORY, px, py, pz);
      Hidden.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (size_t i = 0; i < NInhibitory; ++i) {
      float px, py, pz;
      uniformSphere(px, py, pz, 0.98, false);
      GENNeuron *Neuron = new GENNeuron(j++, GENNeuron::INHIBITORY, px, py, pz);
      Hidden.push_back(Neuron);
      Neurons.push_back(Neuron);
    }
    for (auto &e : Neurons)
      e->computeDistances(Neurons);
  }

  void addSynapse(size_t src, size_t target, double W) {
    Neurons[target]->addSynapse(Neurons[src], W);
  }

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
