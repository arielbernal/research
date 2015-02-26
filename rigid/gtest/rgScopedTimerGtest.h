#ifndef RGSCOPEDTIMERGTEST_H
#define RGSCOPEDTIMERGTEST_H

#include <io/rgScopedTimer.h>

using namespace rg;

TEST(Test_ScopedTimer, ScopedTimer) {
  size_t N = 100000;
  float a = 0;
  double t0 =0, t = 0;
  {
    const rg::scoped_timer timer(t, rg::scoped_timer::unit_us); 
    for (size_t i = 0; i < N; ++i)
      ++a;
  }
  EXPECT_TRUE(t0 <= t);
  t0 = t;
  {
    const rg::scoped_timer timer(t, true, rg::scoped_timer::unit_us); 
    for (size_t i = 0; i < N; ++i)
      ++a;    
  }
  EXPECT_TRUE(t0 <= t);
  t0 = t;
  {
    const rg::scoped_timer timer(t, rg::scoped_timer::unit_us); 
    for (size_t i = 0; i < N; ++i)
      ++a;    
  }
  EXPECT_TRUE(t <= t0);
  EXPECT_EQ(3 * N, a);
}


#endif  // RGSCOPEDTIMERGTEST_H