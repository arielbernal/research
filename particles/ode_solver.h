#ifndef ODESOLVER_H
#define ODESOLVER_H

#include <stdlib.h>
#include <vector>
#include <svector.h>

using namespace svector;

typedef void (*dydtFunc)(float t, std::vector<float4> &y,
                         std::vector<float4> &res, void *dydt_args);

void multVector(std::vector<float4> &y, float k) {
  for (size_t i = 0; i < y.size(); ++i) y[i] *= k;
}

void madVector(std::vector<float4> &c, std::vector<float4> &a, float k) {
  for (size_t i = 0; i < c.size(); ++i) c[i] += a[i] * k;
}

void madVector(std::vector<float4> &c, std::vector<float4> &a,
               std::vector<float4> &b, float k) {
  for (size_t i = 0; i < c.size(); ++i) c[i] = a[i] + b[i] * k;
}

void addVector(std::vector<float4> &c, std::vector<float4> &a,
               std::vector<float4> &b) {
  for (size_t i = 0; i < c.size(); ++i) c[i] = a[i] + b[i];
}

void printVector(const std::string &str, std::vector<float4> &y) {
  std::cout << str << std::endl;
  for (size_t i = 0; i < y.size(); ++i) std::cout << y[i].str() << std::endl;
}

void ODERK4Solver(float t, float h, std::vector<float4> &y,
                  std::vector<float4> &yf, dydtFunc dydt, void *dydt_args) {

  std::vector<float4> T1(y.size());
  std::vector<float4> T2(y.size());

  yf = y;
  dydt(t, y, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 1.0f / 6.0f);

  madVector(T2, y, T1, 1.0f / 2.0f);
  dydt(t + h / 2.0f, T2, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 2.0f / 6.0f);

  madVector(T2, y, T1, 1.0f / 2.0f);
  dydt(t + h / 2.0f, T2, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 2.0f / 6.0f);

  addVector(T2, y, T1);
  dydt(t + h, T2, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 1.0f / 6.0f);
}

void ODERK2Solver(float t, float h, std::vector<float4> &y,
                  std::vector<float4> &yf, dydtFunc dydt, void *dydt_args) {

  std::vector<float4> T1(y.size());
  std::vector<float4> T2(y.size());

  yf = y;
  dydt(t, y, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 1.0f / 2.0f);

  madVector(T2, y, T1, 1.0f);
  dydt(t + h, T2, T1, dydt_args);
  multVector(T1, h);
  madVector(yf, T1, 1.0f / 2.0f);
}

#endif