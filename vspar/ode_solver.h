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
  typedef std::function<void(float, float4v &, float4v &, size_t i)>
      DyDtFunctionScalar;

  void setDyDt(DyDtFunction f) { dydt = f; }

  void setDyDtScalar(DyDtFunctionScalar f) { dydtScalar = f; }

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


typedef std::vector<float> VectorFloat;

class ODESolver1 {
 public:
  typedef std::function<void(float, VectorFloat &, VectorFloat &)>
      DerivativeFunction;

  void setDerivative(DerivativeFunction f) { deriv = f; }

 protected:
  void rkck(VectorFloat &y, VectorFloat &dydx, int n, float x, float h,
            VectorFloat &yout, VectorFloat &yerr)
  // Given values for n variables y[1..n] and their derivatives dydx[1..n] known
  // at x, use the fifth-order Cash-Karp Runge-Kutta method to advance the
  // solution over an interval h and return the incremented variables as
  // yout[1..n]. Also return an estimate of the local truncation error in yout
  // using the embedded fourth-order method. The user supplies the routine
  // derivs(x,y,dydx), which returns derivatives dydx at x.
  {
    int i;
    static const float a2 = 0.2, a3 = 0.3, a4 = 0.6, a5 = 1.0, a6 = 0.875,
                       b21 = 0.2, b31 = 3.0 / 40.0, b32 = 9.0 / 40.0, b41 = 0.3,
                       b42 = -0.9, b43 = 1.2, b51 = -11.0 / 54.0, b52 = 2.5,
                       b53 = -70.0 / 27.0, b54 = 35.0 / 27.0,
                       b61 = 1631.0 / 55296.0, b62 = 175.0 / 512.0,
                       b63 = 575.0 / 13824.0, b64 = 44275.0 / 110592.0,
                       b65 = 253.0 / 4096.0, c1 = 37.0 / 378.0,
                       c3 = 250.0 / 621.0, c4 = 125.0 / 594.0,
                       c6 = 512.0 / 1771.0, dc5 = -277.00 / 14336.0;
    static const float dc1 = c1 - 2825.0 / 27648.0,
                       dc3 = c3 - 18575.0 / 48384.0,
                       dc4 = c4 - 13525.0 / 55296.0, dc6 = c6 - 0.25;
    VectorFloat ak2(n);
    VectorFloat ak3(n);
    VectorFloat ak4(n);
    VectorFloat ak5(n);
    VectorFloat ak6(n);
    VectorFloat ytemp(n);

    // First step.
    for (i = 0; i < n; i++) ytemp[i] = y[i] + b21 * h * dydx[i];
    deriv(x + a2 * h, ytemp, ak2);  // Second step.

    for (i = 0; i < n; i++)
      ytemp[i] = y[i] + h * (b31 * dydx[i] + b32 * ak2[i]);
    deriv(x + a3 * h, ytemp, ak3);  // Third step.
    for (i = 0; i < n; i++)
      ytemp[i] = y[i] + h * (b41 * dydx[i] + b42 * ak2[i] + b43 * ak3[i]);
    deriv(x + a4 * h, ytemp, ak4);  // Fourth step.
    for (i = 0; i < n; i++)
      ytemp[i] = y[i] + h * (b51 * dydx[i] + b52 * ak2[i] + b53 * ak3[i] +
                             b54 * ak4[i]);
    deriv(x + a5 * h, ytemp, ak5);  // Fifth step.
    for (i = 0; i < n; i++)
      ytemp[i] = y[i] + h * (b61 * dydx[i] + b62 * ak2[i] + b63 * ak3[i] +
                             b64 * ak4[i] + b65 * ak5[i]);
    deriv(x + a6 * h, ytemp, ak6);  // Sixth step.
    for (i = 0; i < n; i++)  // Accumulate increments with proper weights.
      yout[i] =
          y[i] + h * (c1 * dydx[i] + c3 * ak3[i] + c4 * ak4[i] + c6 * ak6[i]);

    // Estimate error as difference between fourth and fifth order methods.
    for (i = 0; i < n; i++)
      yerr[i] = h * (dc1 * dydx[i] + dc3 * ak3[i] + dc4 * ak4[i] +
                     dc5 * ak5[i] + dc6 * ak6[i]);
  }


#define SAFETY 0.9
#define PGROW -0.2
#define PSHRNK -0.25
#define ERRCON 1.89e-4
  // The value ERRCON equals(5 / SAFETY) raised to the power(1 / PGROW), use
  // below.

  // Fifth-order Runge-Kutta step with monitoring of local truncation error to
  // ensure accuracyand adjust stepsize. Input are the dependent variable vector
  // y[1..n] and its derivative dydx[1..n] at the starting value of the
  // independent variable x. Also input are the stepsize to be attempted htry,
  // the required accuracy eps, and the vector yscal[1..n] against which the
  // error is scaled. On output, y and x are replaced bytheir new values, hdid
  // is the stepsize that was actuallyaccomplished, and hnext is the estimated
  // next stepsize. derivs is the user-supplied routine that computes the
  // right-hand side derivatives.
  void rkqs(VectorFloat &y, VectorFloat &dydx, int n, float &x, float htry,
            float eps, VectorFloat &yscal, float &hdid, float &hnext) {

    VectorFloat yerr(n);
    VectorFloat ytemp(n);

    float errmax;
    float h = htry;  // Set stepsize to the initial trial value.
    for (;;) {
      rkck(y, dydx, n, x, h, ytemp, yerr);  // Take a step.
      errmax = 0.0f;                        // Evaluate accuracy.
      for (size_t i = 0; i < n; ++i)
        errmax = std::max<float>(errmax, fabs(yerr[i] / yscal[i]));
      errmax /= eps;              // Scale relative to required tolerance.
      if (errmax <= 1.0f) break;  // Step succeeded. Compute size of next step.
      // Truncation error too large, reduce stepsize.
      float htemp = SAFETY * h * std::pow(errmax, PSHRNK);
      // No more than a factor of 10.
      h = (h >= 0.0 ? std::max<float>(htemp, 0.1 * h)
                    : std::min<float>(htemp, 0.1 * h));
      if (h == 0) std::cout << "stepsize underflow in rkqs\n";
    }
    if (errmax > ERRCON)
      hnext = SAFETY * h * pow(errmax, PGROW);
    else
      hnext = 5.0 * h;  // No more than a factor of 5 increase.
    hdid = h;
    x += h;
    for (size_t i = 0; i < n; ++i) y[i] = ytemp[i];
  }

#define MAXSTP 10000
#define TINY 1.0e-30

  void odeint(VectorFloat &ystart, VectorFloat &yend, int nvar, float x1,
              float x2, float eps, float h1, float hmin, int &nok, int &nbad)
  // Runge-Kutta driver with adaptive stepsize control. Integrate starting
  // values ystart[1..nvar] from x1 to x2 with accuracy eps, storing
  // intermediate results in global variables. h1 should be set as a guessed
  // first stepsize, hmin as the minimum allowed stepsize (can be zero). On
  // output nok and nbad are the number of good and bad (but retried and fixed)
  // steps taken, and ystart is replaced byvalues at the end of the integration
  // interval. derivs is the user-supplied routine for calculating the
  // right-hand side derivative, while rkqs is the name of the stepper routine
  // to be used.
  {
    float hnext, hdid;
    VectorFloat yscal(nvar);
    VectorFloat dydx(nvar);
    float x = x1;
    #define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
    float h = SIGN(h1, x2 - x1);
    nok = 0;
    nbad = 0;
    for (size_t i = 0; i < nvar; ++i) yend[i] = ystart[i];

    // Take at most MAXSTP steps.
    for (size_t nstp = 0; nstp < MAXSTP; ++nstp) {
      deriv(x, yend, dydx);

      // Scaling used to monitor accuracy. This general-purpose choice can be
      // modified if need be.
      for (size_t i = 0; i < nvar; ++i)
        yscal[i] = fabs(yend[i]) + fabs(dydx[i] * h) + TINY;

      if ((x + h - x2) * (x + h - x1) > 0.0)
        h = x2 - x;  // If stepsize can overshoot, decrease.

      rkqs(yend, dydx, nvar, x, h, eps, yscal, hdid, hnext);

      if (hdid == h)
        ++nok;
      else
        ++nbad;
      if ((x - x2) * (x2 - x1) >= 0.0) {  // Are we done?
        for (size_t i = 0; i < nvar; ++i) yend[i] = yend[i];
        return;  // Normal exit.
      }
      if (fabs(hnext) <= hmin) std::cout << "Step size too small in odeint";
      h = hnext;
    }
    std::cout << "Too many steps in routine odeint";
  }

 private:
  DerivativeFunction deriv;
};

#endif