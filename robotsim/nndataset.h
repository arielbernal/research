#ifndef NNDATASET_H
#define NNDATASET_H

#include <iostream>
#include <fstream>

template<typename DT = double>
struct NNSample {
  NNSample(size_t InputSize, size_t OutputSize, size_t id)
    : id(id), Input(InputSize), Output(OutputSIze) {}

  NNSample(size_t InputSize, size_t OutputSize, size_t id, DT* data)
    : id(id), Input(InputSize), Output(OutputSize) {
    for (size_t i = 0; i < InputSize; ++i)
      Input[i] = data[i];
    for (size_t i = 0; i < OutputSize; ++i)
      Output[i] = data[i + InputSize];
  }

  NNSample(size_t id, const std::vector<DT>& I, const std::vector<DT>& O)
    : id(id), Input(I), Output(O) {}

  size_t id;
  std::vector<DT> Input;
  std::vector<DT> Output;
};


template<typename DT = double>
class NNDataset {
public:
  typedef NNSample<DT> SampleType;
  typedef typename std::vector<SampleType*>::iterator Iterator;

  NNDataset(size_t InputSize, size_t OutputSize)
    : InputSize(InputSize)
    , OutputSize(OutputSize)
    , N(0)
  {}

  size_t getN() { return N; }

  void addSample(const std::vector<DT>& Input, const std::vector<DT>& Output) {
    SampleType* S = new SampleType(N, Input, Output);
    Samples.push_back(S);
    N = Samples.size();
  }

  void print() {
    for (auto& e : Samples) {
      std::cout << e->Input[0] << " " << e->Input[1] << " " << e->Input[2] << " " <<
        e->Output[0] << " " << e->Output[1] << std::endl;
    }
  }


  bool load(size_t n, const std::string& DataFile) {
    size_t Size = InputSize + OutputSize;
    std::vector<DT> Data(n * Size);

    std::ifstream ifsd(DataFile.c_str(),
      std::ifstream::in | std::ifstream::binary);
    if (!ifsd.is_open()) {
      std::cout << "Error Data file no found : " << DataFile.c_str() << std::endl;
      return false;
    }
    ifsd.read((char*)&Data[0], n * Size * sizeof(DT));
    ifsd.close();

    N = n;

    Samples.resize(N);

    for (size_t i = 0; i < N; ++i) {
      SampleType* S = new SampleType(
        InputSize, OutputSize, i, (DT*)&Data[i * Size]);
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
    for (auto &e : Samples) {
      for (auto &ei : e->Input) {
        ofs.write(reinterpret_cast<char*>(&ei), sizeof(DT));
      }
      for (auto &eo : e->Output) {
        ofs.write(reinterpret_cast<char*>(&eo), sizeof(DT));
      }
    }
    ofs.close();
  }


private:
  size_t InputSize;
  size_t OutputSize;
  size_t N;

  std::vector<SampleType*> Samples;
};



#endif