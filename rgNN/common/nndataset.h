#ifndef NNDATASET
#define NNDATASET

#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>

template <typename DataType, typename FileDataType> class NNDataset {
public:
  NNDataset(size_t Rows, size_t Cols, size_t OutputSize)
      : N(0),
        Size(Rows * Cols),
        Cols(Cols),
        Rows(Rows),
        OutputSize(OutputSize),
        CurrentId(0) {}

  NNDataset(size_t Size, size_t OutputSize)
      : N(0),
        Size(Size),
        Cols(Size),
        Rows(1),
        OutputSize(OutputSize),
        CurrentId(0) {}

  size_t getN() { return N; }
  size_t getSize() { return Size; }
  size_t getRows() { return Rows; }
  size_t getCols() { return Cols; }
  size_t getOutputSize() { return OutputSize; }

  void addSample(std::vector<FileDataType> &sample, uint8_t label) {
    for (auto &e : sample)
      Data.push_back(e);
    Labels.push_back(label);
    N++;
  }

  FileDataType *getData(size_t id) { return &Data[id * Size]; }
  FileDataType *getData() { return &Data[CurrentId * Size]; }
  uint8_t getLabel(size_t id) { return Labels[id]; }
  uint8_t getLabel() { return Labels[CurrentId]; }

  FileDataType getXYValue(size_t id, size_t x, size_t y) {
    return Data[id * Size + y * Cols + x];
  }

  FileDataType getXYValue(size_t x, size_t y) {
      std::cout << Size << std::endl;
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

  DataType *getInput(size_t id) { return &Inputs[id * Size]; }
  DataType *getInput() { return &Inputs[CurrentId * Size]; }
  DataType *getOutput(size_t id) { return &Outputs[id * OutputSize]; }
  DataType *getOutput() { return &Outputs[CurrentId * OutputSize]; }

  bool load(size_t x0, size_t n, const std::string &DataFile,
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
    ifsd.seekg(DataOffset + x0 * Size * sizeof(FileDataType));
    ifsd.read((char *)&Data[0], n * Size * sizeof(FileDataType));
    ifsd.close();

    std::ifstream ifsl(LabelsFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsl.is_open()) {
      std::cout << "Error Labels file no found : " << LabelsFile << std::endl;
      return false;
    }
    ifsl.seekg(LabelsOffset + x0 * sizeof(uint8_t));
    ifsl.read((char *)&Labels[0], n * sizeof(uint8_t));
    ifsl.close();

    N = n;
    return true;
  }

  void generateOutputs() {
    Outputs.resize(N * OutputSize);
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < OutputSize; ++j)
        Outputs[i * OutputSize + j] = Labels[i] == j ? 1 : -1;
  }

  void generateInputs() {
    Inputs.resize(N * Size);
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        Inputs[i * Size + j] = DataType(Data[i * Size + j]);
  }

  void randomizeOrder() {
    for (size_t i = 0; i < N; ++i) {
      size_t id0 = rand() % N;
      size_t id1 = rand() % N;
      std::swap(Labels[id0], Labels[id1]);
      for (size_t k = 0; k < OutputSize; ++k)
        std::swap(Outputs[id0 * OutputSize + k], Outputs[id1 * OutputSize + k]);
      for (size_t k = 0; k < Size; ++k) {
        std::swap(Data[id0 * Size + k], Data[id1 * Size + k]);
        std::swap(Inputs[id0 * Size + k], Inputs[id1 * Size + k]);
      }
    }
  }

private:
  std::vector<FileDataType> Data;
  std::vector<uint8_t> Labels;
  std::vector<DataType> Inputs;
  std::vector<DataType> Outputs;
  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  size_t OutputSize;
  size_t CurrentId;
};

#endif // NNDATASET
