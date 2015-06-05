#ifndef NNDATASET
#define NNDATASET

#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>

template <typename T, typename K> class NNDataset {
public:
  NNDataset(size_t Rows, size_t Cols)
      : N(0), Size(Rows * Cols), Cols(Cols), Rows(Rows), CurrentId(0) {}

  NNDataset(size_t Size)
      : N(0), Size(Size), Cols(Size), Rows(1), CurrentId(0) {}

  size_t getN() { return N; }
  size_t getSize() { return Size; }
  size_t getRows() { return Rows; }
  size_t getCols() { return Cols; }

  void addSample(std::vector<T> &sample, K label) {
    for (auto &e : sample)
      Data.push_back(e);
    Labels.push_back(label);
    N++;
  }

  T *getSample(size_t id) { return &Data[id * Size]; }
  T *getSample() { return &Data[CurrentId * Size]; }
  K getLabel(size_t id) { return Labels[id]; }
  K getLabel() { return Labels[CurrentId]; }

  template <typename S> void getLabel(size_t id, std::vector<S> &pattern) {
    K label = getLabel(id);
    for (size_t i = 0; i < pattern.size(); ++i) {
      if (i == label)
        pattern[i] = 1;
      else
        pattern[i] = 0;
    }
  }

  T getXYValue(size_t id, size_t x, size_t y) {
    return Data[id * Size + y * Cols + x];
  }

  T getXYValue(size_t x, size_t y) {
    return Data[CurrentId * Size + y * Cols + x];
  }

  void setCurrentId(size_t id) {
    if (id < N)
      CurrentId = id;
  }

  size_t getCurrentId() { return CurrentId; }

  void next() {
    if (CurrentId < N - 1)
      CurrentId++;
  }

  void prev() {
    if (CurrentId > 0)
      CurrentId--;
  }

  bool load(size_t n, const std::string &DataFile,
            const std::string &LabelsFile, size_t DataOffset = 0,
            size_t LabelsOffset = 0) {
    Data.resize(n * Size);
    Labels.resize(n);
    std::ifstream ifsd(DataFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsd.is_open()) {
      std::cout << "Error Data file no found : " << DataFile << std::endl;
      return false;
    }
    ifsd.read((char *)&Data[0], DataOffset);
    ifsd.read((char *)&Data[0], n * Size * sizeof(T));
    ifsd.close();

    std::ifstream ifsl(LabelsFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsl.is_open()) {
      std::cout << "Error Labels file no found : " << LabelsFile << std::endl;
      return false;
    }
    ifsl.read((char *)&Labels[0], LabelsOffset);
    ifsl.read((char *)&Labels[0], n * sizeof(K));
    ifsl.close();
    N += n;
    return true;
  }

  void randomizeOrder() {
    for (size_t i = 0; i < N; ++i) {
      size_t id0 = rand() % N;
      size_t id1 = rand() % N;
      std::swap(Labels[id0], Labels[id1]);
      for (size_t k = 0; k < Size; ++k) {
        std::swap(Data[id0 * Size + k], Data[id1 * Size + k]);
      }
    }
  }

private:
  std::vector<T> Data;
  std::vector<K> Labels;
  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  size_t CurrentId;
};

#endif // NNDATASET
