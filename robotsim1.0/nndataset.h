#ifndef NNDATASET_H
#define NNDATASET_H

#include <iostream>
#include <fstream>

template <typename DT = double>
struct NNSample {
  NNSample(size_t InputSize, size_t OutputSize)
      : Input(InputSize), Output(OutputSize) {}

  NNSample(size_t InputSize, size_t OutputSize, DT* data)
      : Input(InputSize), Output(OutputSize) {
    for (size_t i = 0; i < InputSize; ++i) Input[i] = data[i];
    for (size_t i = 0; i < OutputSize; ++i) Output[i] = data[i + InputSize];
  }

  NNSample(const std::vector<DT>& I, const std::vector<DT>& O)
      : Input(I), Output(O) {}

  void add(const NNSample& a) {
    for (size_t i = 0; i < Input.size(); ++i) Input[i] += a.Input[i];
    for (size_t i = 0; i < Output.size(); ++i) Output[i] += a.Output[i];
  }

  void substract(const NNSample& a) {
    for (size_t i = 0; i < Input.size(); ++i) Input[i] -= a.Input[i];
    for (size_t i = 0; i < Output.size(); ++i) Output[i] -= a.Output[i];
  }

  void mult(double k) {
    for (size_t i = 0; i < Input.size(); ++i) Input[i] *= k;
    for (size_t i = 0; i < Output.size(); ++i) Output[i] *= k;
  }

  std::vector<DT> Input;
  std::vector<DT> Output;
};

template <typename DT = double>
class NNDataset {
 public:
  typedef NNSample<DT> SampleType;
  typedef typename std::vector<SampleType*>::iterator Iterator;
  typedef typename std::vector<SampleType*>::const_iterator ConstIterator;

  NNDataset(size_t InputSize, size_t OutputSize)
      : InputSize(InputSize), OutputSize(OutputSize), N(0) {}

  size_t getN() { return N; }

  void addSample(const std::vector<DT>& Input, const std::vector<DT>& Output) {
    SampleType* S = new SampleType(Input, Output);
    Samples.push_back(S);
    N = Samples.size();
  }

  void print() {
    for (auto& e : Samples) {
      std::cout << e->Input[0] << " " << e->Input[1] << " " << e->Input[2]
                << " " << e->Output[0] << " " << e->Output[1] << std::endl;
    }
  }

  bool load(size_t n, const std::string& DataFile) {
    size_t Size = InputSize + OutputSize;
    std::vector<DT> Data(n * Size);

    std::ifstream ifsd(DataFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsd.is_open()) {
      std::cout << "Error Data file no found : " << DataFile.c_str()
                << std::endl;
      return false;
    }
    ifsd.read((char*)&Data[0], n * Size * sizeof(DT));
    ifsd.close();

    N = n;

    Samples.resize(N);

    for (size_t i = 0; i < N; ++i) {
      SampleType* S =
          new SampleType(InputSize, OutputSize, (DT*)&Data[i * Size]);
      Samples[i] = S;
    }
    return true;
  }

  void save(const std::string& DataFile) {
    std::ofstream ofs(DataFile.c_str(), std::ofstream::binary);
    if (!ofs.is_open()) {
      std::cout << "Save error Data file not found" << std::endl;
      return;
    }
    for (auto& e : Samples) {
      for (auto& ei : e->Input) {
        ofs.write(reinterpret_cast<char*>(&ei), sizeof(DT));
      }
      for (auto& eo : e->Output) {
        ofs.write(reinterpret_cast<char*>(&eo), sizeof(DT));
      }
    }
    ofs.close();
  }

  Iterator begin() { return Samples.begin(); }
  Iterator end() { return Samples.end(); }
  size_t size() { return N; }

  ConstIterator begin() const { return Samples.begin(); }
  ConstIterator end() const { return Samples.begin(); }
  size_t size() const { return N; }

  std::vector<SampleType*>& getSamples() { return Samples; }

  SampleType averageSample() {
    SampleType avg(InputSize, OutputSize);
    for (auto& e : Samples) avg.add(*e);
    avg.mult(1.0 / Samples.size());
    return avg;
  }

  void meanCancellation(const SampleType& mean) {
    for (auto& e : Samples) e->substract(mean);
  }

 private:
  size_t InputSize;
  size_t OutputSize;
  size_t N;

  std::vector<SampleType*> Samples;
};

#endif
