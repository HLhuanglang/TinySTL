#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H


#include"test.h"
#include"algorithm/algorithm.h"


namespace TinySTL {
namespace test {
namespace algorithm_test {

bool isBool(int x)
{
return x > 0 ? true : false;
}


TEST(max_test)
{
EXPECT_TRUE(isBool(1));
}


}//end of algorithm_test namespace
}//end of test namespace
}//end of TinySTL namespace

#endif // !ALGORITHM_TEST_H

