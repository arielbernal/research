#include <iostream>
#include <cmath>
#include <queue>
#include "nngen.h"

namespace {
GENNeuralNet NN(2, 1, 2, 1);
std::queue<float> TrainInput;
std::queue<float> TrainOutput;
}

void addTestSample(float x, float y, float c) {
  char cx = char(x);
  char cy = char(y);
  char cc = char(c);
  char mask = 0x04;
  for (size_t i = 0; i < 3; ++i) {
    char sx = (cx & mask) != 0;
    char sy = (cy & mask) != 0;
    char sc = (cc & mask) != 0;
    TrainInput.push(int(sx));
    TrainInput.push(sy);
    TrainOutput.push(sc);
    
     std::cout << "  " << int(sx) << " " << int(sy) << " " << int(sc)
                << std::endl;
    mask >>= 1;
  }
  TrainInput.push(0);
  TrainOutput.push(0);
}
void populateTrainingQueues() {
  std::default_random_engine generator;
  static std::uniform_int_distribution<size_t> uniform(0, 7);
  for (size_t i = 0; i < 1000; ++i) {
    float x = uniform(generator);
    float y = uniform(generator);
    float c = x > 4 && y > 4 ? 1 : 0;
    addTestSample(x, y, c);
    addTestSample(x, y, c);
    addTestSample(x, y, c);
  }
}

int main() {
  //populateTrainingQueues();
  addTestSample(5, 5, 1);
  for (size_t i = 0; i < 800; ++i)
    NN.generateSynapses();
  NN.dump();
  for (size_t i = 0; i < 3; ++i) {
    std::cout << "i = " << i << " ---------------------------------------" << std::endl;
    NN.setInput(TrainInput);
    NN.update();
    NN.dump();
    std::cout << "---------------------------------------" << std::endl;
    NN.feedback(TrainOutput);
    NN.dump();
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
  }

  return 0;
}