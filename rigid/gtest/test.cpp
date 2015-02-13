
#include <gtest/gtest.h>
#include "../SVector.h"
#include "SVectorGtest.h"

// #define EXPECT_ARRAY_EQ(TARTYPE, reference, actual, element_count) \
//   {                                                                \
//     TARTYPE *reference_ = static_cast<TARTYPE *>(reference);       \
//     TARTYPE *actual_ = static_cast<TARTYPE *>(actual);             \
//     for (int cmp_i = 0; cmp_i < element_count; cmp_i++) {          \
//       EXPECT_EQ(reference_[cmp_i], actual_[cmp_i]);                \
//     }                                                              \
//   }




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}