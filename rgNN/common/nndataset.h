#ifndef NNDATASET
#define NNDATASET

#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>

template <typename DataType, typename FileDataType>
class NNDataset {
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

  void addSample(std::vector<FileDataType>& sample, uint8_t label) {
    for (auto& e : sample)
      Data.push_back(e);
    Labels.push_back(label);
    N++;
  }

  FileDataType* getData(size_t id) { return &Data[id * Size]; }
  FileDataType* getData() { return &Data[CurrentId * Size]; }
  uint8_t getLabel(size_t id) { return Labels[id]; }
  uint8_t getLabel() { return Labels[CurrentId]; }

  FileDataType getXYValue(size_t id, size_t x, size_t y) {
    return Data[id * Size + y * Cols + x];
  }

  FileDataType getXYValue(size_t x, size_t y) {
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

  DataType* getInput(size_t id) { return &Inputs[id * Size]; }
  DataType* getInput() { return &Inputs[CurrentId * Size]; }
  DataType* getOutput(size_t id) { return &Outputs[id * OutputSize]; }
  DataType* getOutput() { return &Outputs[CurrentId * OutputSize]; }

  bool load(size_t x0,
            size_t n,
            const std::string& DataFile,
            const std::string& LabelsFile,
            size_t DataOffset = 0,
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
    ifsd.read((char*)&Data[0], n * Size * sizeof(FileDataType));
    ifsd.close();

    std::ifstream ifsl(LabelsFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsl.is_open()) {
      std::cout << "Error Labels file no found : " << LabelsFile << std::endl;
      return false;
    }
    ifsl.seekg(LabelsOffset + x0 * sizeof(uint8_t));
    ifsl.read((char*)&Labels[0], n * sizeof(uint8_t));
    ifsl.close();

    N = n;

    Outputs.resize(N * OutputSize);
    Inputs.resize(N * Size);
    VMean.resize(Size);

    generateOutputs();
    normalizeInputs();
    computeMeanVector();
    processInputs();

    return true;
  }

  void generateOutputs() {
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < OutputSize; ++j)
        Outputs[i * OutputSize + j] = Labels[i] == j ? 1 : -1;
  }

  void normalizeInputs() {
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        Inputs[i * Size + j] = DataType(Data[i * Size + j]) / 256.0f;
  }

  void computeMeanVector() {
    std::fill(VMean.begin(), VMean.end(), 0);
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        VMean[j] += Inputs[i * Size + j];
    for (size_t j = 0; j < Size; ++j)
      VMean[j] /= N;
  }

  void processInputs() {
    // Removing mean values
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j) {
        Inputs[i * Size + j] -= VMean[j];
      }
  }

  DataType computeDistance(DataType* a, DataType* b) {
    DataType d2 = 0;
    for (size_t i = 0; i < Size; ++i) {
      DataType d = a[i] - b[i];
      d2 += d * d;
    }
    return d2 / Size;
  }

  size_t findClosestSample(DataType* input) {
    DataType dmin = computeDistance(getInput(0), input);
    size_t imin = 0;
    for (size_t i = 1; i < N; ++i) {
      DataType d = computeDistance(getInput(i), input);
      if (d < dmin) {
        dmin = d;
        imin = i;
      }
    }
    return imin;
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

  std::vector<DataType>& getMeanVector() { return VMean; }
  void setMeanVector(std::vector<DataType>& V) { VMean = V; }

 private:
  std::vector<FileDataType> Data;  // Data
  std::vector<uint8_t> Labels;     // Data labels
  std::vector<DataType> Inputs;    // Inputs
  std::vector<DataType> Outputs;   // Training/Testing Outputs
  std::vector<DataType> VMean;
  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  size_t OutputSize;
  size_t CurrentId;
};

template <typename DataType = double,
          typename FileDataType = uint8_t,
          typename LabelType = uint8_t>
struct NNSample {
  NNSample(size_t DataSize,
           size_t OutputSize,
           size_t id,
           LabelType label,
           FileDataType* data)
      : Id(id), Label(label), MSE(0), Error(false) {
    Data = new FileDataType[DataSize];
    Input = new DataType[DataSize];
    Output = new DataType[OutputSize];
    for (size_t j = 0; j < DataSize; ++j)
      Data[j] = data[j];
  }

  NNSample(size_t DataSize, size_t OutputSize)
      : Id(0), Label(0), MSE(0), Error(false) {
    Data = new FileDataType[DataSize];
    Input = new DataType[DataSize];
    Output = new DataType[OutputSize];
  }

  ~NNSample() {
    delete Data;
    delete Input;
    delete Output;
  }

  FileDataType* Data;
  DataType* Input;
  DataType* Output;
  size_t Id;
  LabelType Label;
  DataType MSE;
  bool Error;
};

template <typename DataType = double,
          typename FileDataType = uint8_t,
          typename LabelType = uint8_t>
class NNDataset1 {
 public:
  typedef NNSample<DataType, FileDataType, LabelType> SampleType;
  typedef typename std::vector<
      NNSample<DataType, FileDataType, LabelType>*>::iterator Iterator;

  NNDataset1(size_t Rows, size_t Cols, size_t OutputSize)
      : MeanSample(0),
        N(0),
        Size(Rows * Cols),
        Cols(Cols),
        Rows(Rows),
        OutputSize(OutputSize),
        CurrentId(0) {}

  NNDataset1(size_t Size, size_t OutputSize)
      : MeanSample(0),
        N(0),
        Size(Size),
        Cols(Size),
        Rows(1),
        OutputSize(OutputSize),
        CurrentId(0) {}

  size_t getN() { return Filter.size(); }
  size_t getSize() { return Size; }
  size_t getRows() { return Rows; }
  size_t getCols() { return Cols; }
  size_t getOutputSize() { return OutputSize; }
  size_t getNSamples() { return N; }

  Iterator begin() { return Filter.begin(); }
  Iterator end() { return Filter.end(); }

  bool load(size_t x0,
            size_t n,
            const std::string& DataFile,
            const std::string& LabelsFile,
            size_t DataOffset = 0,
            size_t LabelsOffset = 0) {
    std::vector<FileDataType> Data(n * Size);
    std::vector<LabelType> Labels(n);

    std::ifstream ifsd(DataFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsd.is_open()) {
      std::cout << "Error Data file no found : " << DataFile << std::endl;
      return false;
    }
    ifsd.seekg(DataOffset + x0 * Size * sizeof(FileDataType));
    ifsd.read((char*)&Data[0], n * Size * sizeof(FileDataType));
    ifsd.close();

    std::ifstream ifsl(LabelsFile.c_str(),
                       std::ifstream::in | std::ifstream::binary);
    if (!ifsl.is_open()) {
      std::cout << "Error Labels file no found : " << LabelsFile << std::endl;
      return false;
    }
    ifsl.seekg(LabelsOffset + x0 * sizeof(uint8_t));
    ifsl.read((char*)&Labels[0], n * sizeof(uint8_t));
    ifsl.close();

    N = n;

    Samples.resize(N);
    Filter.resize(N);

    for (size_t i = 0; i < N; ++i) {
      SampleType* S = new SampleType(
          Size, OutputSize, i, Labels[i], (uint8_t*)&Data[i * Size]);
      Samples[i] = S;
      Filter[i] = S;
    }

    generateOutputs();
    normalizeInputs();
    computeMeanVector();
    processInputs();

    return true;
  }

  void computeMeanVector() {
    if (MeanSample)
      delete MeanSample;
    MeanSample = new SampleType(Size, OutputSize);
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        MeanSample->Input[j] += Samples[i]->Input[j];
    for (size_t j = 0; j < Size; ++j)
      MeanSample->Input[j] /= N;
  }

  void generateOutputs() {
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < OutputSize; ++j)
        Samples[i]->Output[j] = Samples[i]->Label == j ? 1 : -1;
  }

  void normalizeInputs() {
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        Samples[i]->Input[j] = DataType(Samples[i]->Data[j]) / 256.0f;
  }

  void processInputs() {
    for (size_t i = 0; i < N; ++i)
      for (size_t j = 0; j < Size; ++j)
        Samples[i]->Input[j] -= MeanSample->Input[j];
  }

  void addFilterByLabel(LabelType Label) {
    std::vector<SampleType*> FilterTemp = Filter;
    Filter.clear();
    for (auto& e : FilterTemp)
      if (e->Label == Label)
        Filter.push_back(e);
  }

  void addFilterByError() {
    std::vector<SampleType*> FilterTemp = Filter;
    Filter.clear();
    for (auto& e : FilterTemp)
      if (e->Error)
        Filter.push_back(e);
  }

  void clearFilter() {
    Filter.clear();
    for (auto& e : Samples)
      Filter.push_back(e);
  }

  SampleType* getMeanSample() { return MeanSample; }
  void setMeanSample(const SampleType* Sample) {
    for (size_t i = 0; i < OutputSize; ++i)
      MeanSample->Input[i] = Sample->Input[i];
  }

 private:
  std::vector<SampleType*> Samples;
  std::vector<SampleType*> Filter;
  SampleType* MeanSample;

  size_t N;
  size_t Size;
  size_t Cols;
  size_t Rows;
  size_t OutputSize;
  size_t CurrentId;
};

#endif  // NNDATASET
