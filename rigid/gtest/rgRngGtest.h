#ifndef RGRNGGTEST_H
#define RGRNGGTEST_H

#include <math/rgRng.h>

using namespace rg;

TEST(Test_Rng, UniformFloat) {
  float a = uniform();
  EXPECT_TRUE(0 <= a && a <= 1);

  float b = uniform(3.0f, 5.0f);
  EXPECT_TRUE(3 <= b && b <= 5);
}

TEST(Test_Rng, UniformDouble) {
  double a = uniform<double>();
  EXPECT_TRUE(0 <= a && a <= 1);

  double b = uniform<double>(3, 5);
  EXPECT_TRUE(3 <= b && b <= 5);
}

TEST(Test_Rng, NormalFloat) {
  const size_t N = 1000;
  {
    float a = 0;
    for (size_t i = 0; i < N; ++i) a += normal();
    a /= N;
    EXPECT_TRUE(-1 <= a && a <= 1);
  }
  {
    float a = 0;
    for (size_t i = 0; i < N; ++i) a += normal(5.0f, 3.0f);
    a /= N;
    EXPECT_TRUE(4 <= a && a <= 6);
  }
}

TEST(Test_Rng, NormalDouble) {
  const size_t N = 1000;
  {
    double a = 0;
    for (size_t i = 0; i < N; ++i) a += normal<double>();
    a /= N;
    EXPECT_TRUE(-1 <= a && a <= 1);
  }
  {
    double a = 0;
    for (size_t i = 0; i < N; ++i) a += normal<double>(5, 3);
    a /= N;
    EXPECT_TRUE(4 <= a && a <= 6);
  }
}

#endif  // RGRNGGTEST_H