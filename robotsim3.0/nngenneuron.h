#ifndef NNGENNEURON_H
#define NNGENNEURON_H

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
    if (nntype == INHIBITORY)
      W *= -1;
    auto e = PosSynapses.find(PosNeuron->id);
    if (e == PosSynapses.end()) {
      GENSynapse *S = new GENSynapse(this, PosNeuron, W);
      PosNeuron->PreSynapses[id] = S;
      PosSynapses[PosNeuron->id] = S;
    } else {
      e->second->W += W;
      // std::cout << "Multiple synapse = " << e->second->W << std::endl;
    }
  }

  void deleteSynapse(GENSynapse *S) {
    PosSynapses.erase(S->PosNeuron->id);
    S->PosNeuron->deletePreSynapse(S);
  }

  void deletePreSynapse(GENSynapse *S) { PreSynapses.erase(S->PreNeuron->id); }

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
    v = 0;
    for (auto &e : PreSynapses) {
      v += e.second->W * e.second->PreNeuron->Ap;
      // std::cout << "    " << e.second->PreNeuron->id << " - " << e.second->W
      //           << " - " << e.second->PreNeuron->Ap << std::endl;
    }
    std::cout << id << " " << v << std::endl;
    if (v > theta) {
      Ap = 1;
      v = H;
    }
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
    float neuronSize = 0.18;
    static std::default_random_engine generator;
    static std::normal_distribution<float> normal(0, 4 * neuronSize);
    float dd = fabs(normal(generator)) + neuronSize;
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
      float PosW = 0.5f * 20 * theta / 10.0f;

      std::uniform_int_distribution<size_t> uniform(0, idmax);
      size_t idd = idmax; // uniform(generator);
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
      printf("  From Id = %zu - W = %f \n", S->PreNeuron->id, S->W);
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

#endif // FFNN3L_H
