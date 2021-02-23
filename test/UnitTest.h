#ifndef UNITTEST_H
#define UNITTEST_H
#include <ctime>
#include <iostream>
#include <vector>

#include "hldb_log.h"
#include "lib/redbud/io/color.h"

#define green_fg redbud::io::hfg::green
#define red_fg redbud::io::hfg::red
#define blue_fg redbud::io::hfg::blue
#define white_fg redbud::io::hfg::white
#define yellow_fg redbud::io::hfg::yellow

#define yellow_bg redbud::io::hbg::yellow

//测试用例
class TestCase {
 public:
  TestCase(const char* name)
      : test_case_name_(name), result_(true), failed_(0), passed_(0) {}
  virtual void Run() = 0;

 public:
  const char* test_case_name_;  //测试例子名称
  bool result_;                 //测试案例执行结果
  size_t failed_;               //测试案例中宏断言失败个数
  size_t passed_;               //测试案例中宏断言成果个数
};

//测试集合
class UnitTest {
 public:
  static UnitTest* GetInstance();
  TestCase* AddTestCase(TestCase* test_case);
  void StartTest();

 private:
  UnitTest();
  void DisplayResult(const char* test_case_name, size_t passed, size_t failed,
                     bool result);

 public:
  TestCase* curr_test_case_;      //当前的测试案例
  size_t test_case_failed_num_;   //测试案例失败的个数
  size_t test_case_succeed_num_;  //测试案例成功的个数

 protected:
  std::vector<TestCase*> testcase_;  //存放所有的测试案例
};

/********************************************************************************************************/
#define RUN_ALL_TESTS() UnitTest::GetInstance()->StartTest()

#define TEST(name) STL_TEST(name)

// 将name替换成name_TEST
#define TESTCASE_NAME(name) name##_TEST

// 通过宏定义来实现一个类，继承TestCase,主要是为了重写Run方法
// TESTCASE_NAME(name) 就是类名字
// #name是转为字符串的意思
// static TestCase* const testcase_; 避免了手动添加的操作
#define STL_TEST(name)                                                      \
  class TESTCASE_NAME(name) : public TestCase {                             \
   public:                                                                  \
    TESTCASE_NAME(name)                                                     \
    (const char* case_name) : TestCase(case_name){};                        \
    virtual void Run();                                                     \
                                                                            \
   private:                                                                 \
    static TestCase* const testcase_;                                       \
  };                                                                        \
                                                                            \
  TestCase* const TESTCASE_NAME(name)::testcase_ =                          \
      UnitTest::GetInstance()->AddTestCase(new TESTCASE_NAME(name)(#name)); \
  void TESTCASE_NAME(name)::Run()

// 真假断言
// EXPECT_TRUE  验证条件: Condition 为 true
// EXPECT_FALSE 验证条件: Condition 为 false
#define EXPECT_TRUE(Condition)                                   \
  do {                                                           \
    if (Condition) {                                             \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO("EXPECT_TRUE succeed!");                           \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO("EXPECT_TRUE failed!");                            \
    }                                                            \
  } while (0)

#define EXPECT_FALSE(Condition)                                  \
  do {                                                           \
    if (!Condition) {                                            \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_FALSE succeeded!");                       \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_FALSE failed!");                          \
    }                                                            \
  } while (0)

// 比较断言
// EXPECT_EQ(v1,v2) 相等
// EXPECT_NQ(v1,v2) 不相等
// EXPECT_GT(v1,v2) 大于
// EXPECT_LT(v1,v2) 小于
// EXPECT_GE(v1,v2) 大于等于
// EXPECT_LE(v1,v2) 小于等于
#define EXPECT_EQ(v1, v2)                                        \
  do {                                                           \
    if (v1 == v2) {                                              \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)

#define EXPECT_NQ(v1, v2)                                        \
  do {                                                           \
    if (v1 != v2) {                                              \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)

#define EXPECT_GT(v1, v2)                                        \
  do {                                                           \
    if (v1 > v2) {                                               \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)

#define EXPECT_LT(v1, v2)                                        \
  do {                                                           \
    if (v1 < v2) {                                               \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)

#define EXPECT_GE(v1, v2)                                        \
  do {                                                           \
    if (v1 >= v2) {                                              \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)

#define EXPECT_LE(v1, v2)                                        \
  do {                                                           \
    if (v1 <= v2) {                                              \
      UnitTest::GetInstance()->curr_test_case_->result_ = true;  \
      UnitTest::GetInstance()->curr_test_case_->passed_++;       \
      LOGINFO(" EXPECT_EQ succeeded!");                          \
    } else {                                                     \
      UnitTest::GetInstance()->curr_test_case_->result_ = false; \
      UnitTest::GetInstance()->curr_test_case_->failed_++;       \
      LOGINFO(" EXPECT_EQ failed!");                             \
    }                                                            \
  } while (0)
#endif  // !UNITTEST_H
