#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include "UnitTest.h"
#include "algorithm/algorithm.h"

namespace TinySTL {
bool Test() { return true; }

TEST(Holo1) { EXPECT_TRUE(Test()); }

TEST(Holo2) { EXPECT_FALSE(Test()); }
}  // namespace TinySTL
#endif  // !ALGORITHM_TEST_H
