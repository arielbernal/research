#ifndef ODESOLVER_H
#define ODESOLVER_H

#include <stdlib.h>
#include <vector>
#include <svector.h>
#include <functional>

using namespace svector;

class ODESolver {
public:

  typedef std::function<void(float, float4v &, float4v &)> DyDtFunction;
  typedef std::function<void(float, float4v &, float4v &, size_t i)> DyDtFunctionScalar;

  void setDyDt(DyDtFunction f) {
    dydt = f;
  }

  void setDyDtScalar(DyDtFunctionScalar f) {
    dydtScalar = f;
  }


  void RK4Solve(float t, float h, float4v &y, float4v &yf) {

    float4v T1(y.size());
    float4v T2(y.size());

    yf = y;

    dydt(t, y, T1);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 6.0f);

    madVector(T2, y, T1, 1.0f / 2.0f);
    dydt(t + h / 2.0f, T2, T1);
    multVector(T1, h);
    madVector(yf, T1, 2.0f / 6.0f);

    madVector(T2, y, T1, 1.0f / 2.0f);
    dydt(t + h / 2.0f, T2, T1);
    multVector(T1, h);
    madVector(yf, T1, 2.0f / 6.0f);

    addVector(T2, y, T1);
    dydt(t + h, T2, T1);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 6.0f);
  }

  void RK2Solve(float t, float h, float4v &y, float4v &yf) {

    float4v T1(y.size());
    float4v T2(y.size());

    yf = y;
    dydt(t, y, T1);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 2.0f);

    madVector(T2, y, T1, 1.0f);
    dydt(t + h, T2, T1);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 2.0f);
  }

  void RK2Solve(float t, float h, float4v &y, float4v &yf, size_t id) {

    float4v T1(y.size());
    float4v T2(y.size());

    yf = y;
    dydtScalar(t, y, T1, id);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 2.0f);

    madVector(T2, y, T1, 1.0f);
    dydtScalar(t + h, T2, T1, id);
    multVector(T1, h);
    madVector(yf, T1, 1.0f / 2.0f);
  }


protected:
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

private:
  DyDtFunction dydt;
  DyDtFunctionScalar dydtScalar;

};

#endif