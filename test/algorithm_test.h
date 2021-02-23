#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include <vector>

#include "UnitTest.h"
#include "algorithm/algorithm.h"

namespace TinySTL {
TEST(swap_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  auto v1_before_swap = v1;
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 8};
  auto v2_before_swap = v2;
  TinySTL::swap(v1, v2);
  EXPECT_EQ(v1, v2_before_swap);
  EXPECT_EQ(v2, v1_before_swap);
}

TEST(max_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 8};
  EXPECT_LT(v1, TinySTL::max(v1, v2));
}

TEST(min_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 8};
  EXPECT_GT(v2, TinySTL::min(v1, v2));
}

TEST(iter_swap_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 8};
  TinySTL::iter_swap(v1.begin(), v2.end() - 1);
  std::vector<int> v1_after_swap = {8, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2_after_swap = {1, 2, 3, 4, 5, 6, 1};
  EXPECT_EQ(v1, v1_after_swap);
  EXPECT_EQ(v2, v2_after_swap);
}

TEST(equal_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v3 = {1, 2, 3, 4, 5, 6, 8};
  EXPECT_TRUE(TinySTL::equal(v1.begin(), v1.end(), v2.begin()));
  EXPECT_FALSE(TinySTL::equal(v1.begin(), v1.end(), v3.begin()));
}

TEST(fill_test) {
  std::vector<int> v1 = {1, 3, 5, 7, 9};
  TinySTL::fill(v1.begin(), v1.end(), 3);
  std::vector<int> v1_after_fill = {3, 3, 3, 3, 3};
  EXPECT_EQ(v1, v1_after_fill);
}

TEST(fill_n_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  TinySTL::fill_n(v1.begin(), 5, 0);
  std::vector<int> v1_after_fill_n = {0, 0, 0, 0, 0, 6, 7, 8, 9, 10};
  EXPECT_EQ(v1, v1_after_fill_n);
}
}  // namespace TinySTL
#endif  // !ALGORITHM_TEST_H
