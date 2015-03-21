#ifndef RGRNG_H
#define RGRNG_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <cstddef>
#include <cassert>
#include <limits>
#include <sstream>

#ifndef M_SQRT_2PI
#define M_SQRT_2PI 2.5066282746270f
#endif

namespace rg {

// random numbers using C++ generator [0..1]
template <typename T = float>
T uniform() {
  return rand() / T(RAND_MAX);  // rand return [0..RAND_MAX]
}

template <typename T = float>
T uniform(T vmin, T vmax) {
  return vmin + uniform<T>() * (vmax - vmin);
}

template <typename T = float>
T normal() {
  T a = uniform<T>();
  T b = uniform<T>();
  return std::sqrt(static_cast<T>(-2.0) * std::log(a + 0.000001)) *
         std::cos(static_cast<T>(2.0) * M_PI * b);
}

template <typename T = float>
T normal(T mu, T sigma) {
  return normal<T>() * sigma + mu;
}

template <typename T = float>
T normal(T mu, T sigma, T vmin, T vmax) {
  T v = normal<T>(mu, sigma);
  if (v < vmin) {
    v = vmin;
  } else if (v > vmax) {
    v = vmax;
  }
  return v;
}

}  // namespace rg

#endif  // RGRNG_H
