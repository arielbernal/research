#ifndef NNDATASET
#define NNDATASET

#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>

class NNDataset {
public:
  NNDataset(size_t N, size_t Size)
      : Data(N * Size), Labels(N), N(N), Size(Size), Loaded(false), Cols(Size),
        Rows(1), CurrentId(0) {}

  NNDataset(size_t N, size_t Rows, size_t Cols)
      : Data(N * Rows * Cols), Labels(N), N(N), Size(Rows * Cols),
        Loaded(false), Cols(Cols), Rows(Rows), CurrentId(0) {}

  uint8_t getN() { return N; }

  uint8_t getSize() { return Size; }

  uint8_t *getSample(size_t id) { return &Data[id * Size]; }

  uint8_t getLabel(size_t id) { return Labels[id]; }

  uint8_t getXYValue(size_t id, size_t x, size_t y) {
    return Data[id * Size + y * Cols + x];
  }

  uint8_t getLabel() { return Labels[CurrentId]; }

  uint8_t getXYValue(size_t x, size_t y) {
    return Data[CurrentId * Size + y * Cols + x];
  }

  void setCurrentId(size_t id) {
    if (id >= 0 && id < N) {
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
  std::vector<uint8_t> Data;
  std::vector<uint8_t> Labels;
  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  bool Loaded;
  size_t CurrentId;
};

#endif // NNDATASET
