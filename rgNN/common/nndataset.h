#ifndef NNDATASET
#define NNDATASET

#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>

template <typename T, typename K> class NNDataset {
public:
  NNDataset(size_t N, size_t Size)
      : Data(N * Size),
        Labels(N),
        N(N),
        Size(Size),
        Cols(Size),
        Rows(1),
        CurrentId(0),
        Loaded(false) {}

  NNDataset(size_t N, size_t Rows, size_t Cols)
      : Data(N * Rows * Cols),
        Labels(N),
        N(N),
        Size(Rows * Cols),
        Cols(Cols),
        Rows(Rows),
        CurrentId(0),
        Loaded(false) {}

  NNDataset(size_t Size) : N(0), Size(Size), Cols(Size), Rows(1), CurrentId(0),
      Loaded(false) {}

  void set(std::vector<T> &data, std::vector<K> &labels) {
    Data.clear();
    Data.resize(data.size());
    Labels.clear();
    Labels.resize(Labels.size());
    std::copy(data.begin(), data.end(), Data);
    std::copy(labels.begin(), labels.end(), Labels);
  }

  void addSample(std::vector<T> &sample, K label) {
    for (auto &e : sample)
      Data.push_back(e);
    Labels.push_back(label);
    N++;
  }

  size_t getN() { return N; }

  size_t getSize() { return Size; }

  T *getSample(size_t id) { return &Data[id * Size]; }

  K getLabel(size_t id) { return Labels[id]; }

  template <typename S> void getLabel(size_t id, std::vector<S> &pattern) {
    K label = getLabel(id);
    for (size_t i = 0; i < pattern.size(); ++i) {
      if (i == label)
        pattern[i] = 1;
      else
        pattern[i] = 0;
    }
  }

  uint8_t getXYValue(size_t id, size_t x, size_t y) {
    return Data[id * Size + y * Cols + x];
  }

  T *getSample() { return &Data[CurrentId * Size]; }

  K getLabel() { return Labels[CurrentId]; }

  T getXYValue(size_t x, size_t y) {
    return Data[CurrentId * Size + y * Cols + x];
  }

  void setCurrentId(size_t id) {
    if (id < N) {
      CurrentId = id;
    }
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

  bool isLoaded() { return Loaded; }

  bool load(const std::string &DataFile, size_t DataOffset,
            const std::string &LabelsFile, size_t LabelsOffset) {
    Loaded =
        loadData(DataFile, DataOffset) && loadLabels(LabelsFile, LabelsOffset);
    if (Loaded)
      std::cout << "NNDataset Loaded" << std::endl;
    return Loaded;
  }

protected:
  bool loadData(const std::string &Filename, size_t Offset = 0) {
    std::ifstream ifs(Filename.c_str(),
                      std::ifstream::in | std::ifstream::binary);
    if (!ifs.is_open()) {
      std::cout << "Error data file no found" << std::endl;
      return false;
    }
    ifs.read((char *)&Data[0], Offset);
    ifs.read((char *)&Data[0], N * Size);
    ifs.close();
    return true;
  }

  bool loadLabels(const std::string &Filename, size_t Offset = 0) {
    std::ifstream ifs(Filename, std::ifstream::in | std::ifstream::binary);
    if (!ifs.is_open()) {
      std::cout << "Error labels file no found" << std::endl;
      return false;
    }
    ifs.read((char *)&Labels[0], Offset);
    ifs.read((char *)&Labels[0], N);
    ifs.close();
    return true;
  }

private:
  std::vector<T> Data;
  std::vector<K> Labels;
  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  size_t CurrentId;
  bool Loaded;
};

#endif // NNDATASET
