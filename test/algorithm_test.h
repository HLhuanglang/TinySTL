﻿#ifndef ALGORITHM_TEST_H
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

TEST(copy_test) {
  // todo
}

TEST(all_of_test) {
  std::vector<int> v1 = {2, 2, 2, 4, 6, 6};
  EXPECT_TRUE(TinySTL::all_of(v1.begin(), v1.end(),
                              [](int i) { return (i % 2 == 0); }));
}

TEST(any_of_test) {
  std::vector<int> v1 = {1, 3, 5, 7, 9};
  std::vector<int> v2 = {1, 2, 3, 5, 7, 9};
  EXPECT_FALSE(
      TinySTL::any_of(v1.begin(), v1.end(), [](int i) { return i == 2; }));
  EXPECT_TRUE(
      TinySTL::any_of(v2.begin(), v2.end(), [](int i) { return i == 2; }));
}

TEST(for_each_test) {
  std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> v2 = {2, 3, 4, 5, 6, 7, 8};
  // typedef typename std::vector<int>::iterator iterator;
  TinySTL::for_each(v1.begin(), v1.end(), [](int &i) { i++; });
  EXPECT_EQ(v1, v2);
}

TEST(count_test) {
  std::vector<int> v1 = {1, 44, 5, 6, 7, 8, 9, 0, 15, 6};
  EXPECT_EQ(1, TinySTL::count(v1.begin(), v1.end(), 44));
  EXPECT_EQ(1, TinySTL::count(v1.begin(), v1.end(), 15));
  EXPECT_EQ(2, TinySTL::count(v1.begin(), v1.end(), 6));
}

TEST(count_if_test) {
  std::vector<int> v1 = {1, 5, 77, 8, 9, 0, 1};
  size_t t = TinySTL::count_if(v1.begin(), v1.end(), [](int i) {
    if (i > 50) {
      return true;
    } else {
      return false;
    }
  });
  EXPECT_EQ(1, t);
}

// TEST(mismatch_test) {
//  // todo
//  // 该算法存在bug
//  std::vector<int> v1 = {1, 2, 3, 4, 5};
//  std::vector<int> v2 = {1, 2, 3};
//  // std::vector<int> v3 = {1, 2, 3, 4, 5, 6};
//  // std::vector<int> v4 = {1, 2, 4};
//  // std::vector<int> v5 = {0, 2, 3};
//  EXPECT_EQ(*TinySTL::mismatch(v1.begin(), v1.end(), v2.begin()).first, 4);
//  EXPECT_EQ(TinySTL::mismatch(v1.begin(), v1.end(), v2.begin()).second,
//            v2.end());
//}
}  // namespace TinySTL
#endif  // !ALGORITHM_TEST_H
