#ifndef NNGEN_H
#define NNGEN_H

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <list>
#include <map>
#include <chrono>
#include "nndataset.h"

#define SIGMOID_A (1.715904709)
#define SIGMOID_B (0.6666666667)
#define SIGMOID_A2 (SIGMOID_A *SIGMOID_A)
#define SIGMOID_BA (SIGMOID_B / SIGMOID_A)
#define DSIGMOID(S) (SIGMOID_BA *(SIGMOID_A2 - S *S))
#define SIGMOID(x) (SIGMOID_A *tanh(SIGMOID_B *x))
//#define SIGMOID(x) (tanh(x))

struct GENNeuron;

struct GENSynapse {
  GENSynapse(GENNeuron *PreNeuron, GENNeuron *PosNeuron, double W)
      : PreNeuron(PreNeuron), PosNeuron(PosNeuron), W(W) {}
  GENNeuron *PreNeuron;
  GENNeuron *PosNeuron;
  double W; // weight
};

struct GENNeuron {
  enum { INPUT, OUTPUT, EXCITATORY, INHIBITORY };
  GENNeuron(size_t id, size_t nntype, float x, float y, float z)
      : id(id), nntype(nntype), x(x), y(y), z(z), alive(true), v(0), theta(0.5),
        Ap(0), Rp(0), H(-0.2), D(0.2), Dw(0.01) {}

  ~GENNeuron() {
    for (auto &e : PreSynapses)
      delete e.second;
    PosSynapses.clear();
    PreSynapses.clear();
  }

  void addSynapse(GENNeuron *PosNeuron, double W = 0) {
    if (nntype == INPUT)
      W = 1;
    auto e = PosSynapses.find(PosNeuron->id); 
    if (e == PosSynapses.end()) {
      GENSynapse *S = new GENSynapse(this, PosNeuron, W);
      PosNeuron->PreSynapses[id] = S;
      PosSynapses[PosNeuron->id] = S;
    }
    else {
      e->second->W += W;
      std::cout << "Multiple synapse = " << e->second->W << std::endl;
    }
  }

  void deleteSynapse(GENSynapse *S) {
    PosSynapses.erase(S->PosNeuron->id);
    S->PosNeuron->deletePreSynapse(S);
  }

  void deletePreSynapse(GENSynapse *S) {
    PreSynapses.erase(S->PreNeuron->id);
  }

  void deleteDeadSynapses() {
    auto I = PreSynapses.begin();
    while (I != PreSynapses.end()) {
      if (I->second->W == 0) {
        deleteSynapse(I->second);
      }
    }
  }

  void update() {
    Ap = 0;
    for (auto &e : PreSynapses)
      v += e.second->W * e.second->PreNeuron->Ap;
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

  void updateSynapses() {
    for (auto &e : PreSynapses) {
      GENSynapse *S = e.second;
      if (S->PreNeuron->nntype == EXCITATORY && S->PreNeuron->Ap == 1) {
        if (Ap == 1)
          S->W += Dw;
        else
          S->W -= Dw;
        if (S->W > 1)
          S->W = 1;
        if (S->W < 0)
          S->W = 0;
      } else if (S->PreNeuron->nntype == INHIBITORY && S->PreNeuron->Ap == 1) {
        if (Ap == 1)
          S->W += Dw;
        else
          S->W -= Dw;
        if (S->W > 0)
          S->W = 0;
        if (S->W < -1)
          S->W = -1;
      }
    }
  }

  void computeDistances(const std::vector<GENNeuron *> &Neurons) {
    Distances.resize(Neurons.size() - 1);
    size_t j = 0;
    for (auto &e : Neurons) {
      if ((e->id != id) && !(e->nntype == INPUT) &&
          !((e->nntype == OUTPUT) && (nntype == OUTPUT))) {
        float dx = e->x - x;
        float dy = e->y - y;
        float dz = e->z - z;
        float d = sqrt(dx * dx + dy * dy + dz * dz);
        std::pair<size_t, float> p(e->id, d);
        Distances[j++] = p;
      }
    }
    Distances.resize(j);
    std::sort(
        Distances.begin(), Distances.end(),
        [](const std::pair<size_t, float> &a,
           const std::pair<size_t, float> &b) { return a.second < b.second; });
  }

  void createRandomSynapse(const std::vector<GENNeuron *> &Neurons) {
    static std::default_random_engine generator;
    static std::normal_distribution<float> normal(0, 0.2f);
    float dd = fabs(normal(generator)) + 0.07;
    int idmax = -1;
    float dmax = 0;
    for (size_t i = 0; i < Distances.size(); ++i) {
      auto e = Distances[i];
      if (e.second > dd) {
        break;
      } else {
        idmax = i;
        dmax = e.second;
      }
    }

    if (idmax >= 0) {
      float PosW = 1;
      std::uniform_int_distribution<size_t> uniform(0, idmax);
      
      size_t idd = idmax;//uniform(generator);
      std::cout << "HERE ------ . " << dmax << "   " << idmax << " Selected = " << idd << std::endl;
      size_t idPosN = Distances[idd].first;
      addSynapse(Neurons[idPosN], PosW);
    }
  }

  std::string getTypeStr() {
    switch (nntype) {
    case INPUT:
      return "INPUT";
    case OUTPUT:
      return "OUTPUT";
    case INHIBITORY:
      return "INHIBITORY";
    case EXCITATORY:
      return "EXCITATORY";
    }
    return "ERROR";
  }

  void print() {
    printf("Id = %zu - Type = %s - Ap = %f - v = %f\n", id,
           getTypeStr().c_str(), Ap, v);
    for (auto &e : PreSynapses) {
      GENSynapse *S = e.second;
      printf("  From Id = %zu - W = %f \n", S->PreNeuron->id,
             S->W);
    }
  }

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
  double Dw;    // NeuroPlasticity constant
  std::map<size_t, GENSynapse *> PreSynapses;
  std::map<size_t, GENSynapse *> PosSynapses;
  std::vector<std::pair<size_t, float> > Distances;
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

  void feed(const std::vector<double> &In) {
    for (size_t i = 0; i < Input.size(); ++i)
      Input[i]->Ap = In[i];
    for (auto &e : Hidden)
      e->update();
    for (auto &e : Output)
      e->update();
  }

  void generateRandomSynapse() {
    static std::uniform_int_distribution<size_t> dist(0, Neurons.size() - 1);
    size_t id = dist(generator);
    std::cout << "ID = " << id << std::endl;
    Neurons[id]->createRandomSynapse(Neurons);
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

  void addHiddenNeuron(size_t nntype) {
    auto uniform =
        std::bind(std::uniform_real_distribution<float>(0, 1), generator);
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
