#include "UnitTest.h"

#include <string>

UnitTest::UnitTest() {
  this->curr_test_case_ = nullptr;
  this->test_case_succeed_num_ = 0;
  this->test_case_failed_num_ = 0;
}

UnitTest* UnitTest::GetInstance() {
  static UnitTest instance;
  return &instance;
}

TestCase* UnitTest::AddTestCase(TestCase* test_case) {
  this->testcase_.emplace_back(test_case);
  return test_case;
}

void UnitTest::StartTest() {
  std::string begin_msg = R"(
+----------------------+
-Begin TinySTL UnitTest-
+----------------------+
	)";
  std::cout << green_fg << begin_msg << white_fg << std::endl;
  std::cout << yellow_fg << "========================" << white_fg << std::endl;
  for (auto n : testcase_) {
    TestCase* test_temp = n;
    curr_test_case_ = test_temp;
    //执行单个测试案例的测试过程
    test_temp->Run();
    //统计测试案例的通过情况
    if (test_temp->result_) {
      test_case_succeed_num_++;
    } else {
      test_case_failed_num_++;
    }
    //打印当前测试案例的测试情况
    DisplayResult(test_temp->test_case_name_, test_temp->passed_,
                  test_temp->failed_, test_temp->result_);
    std::cout << yellow_fg << "========================" << white_fg
              << std::endl;
  }

  std::string end_msg = R"(
+----------------------+
--End TinySTL UnitTest--
+----------------------+
	)";
  std::cout << green_fg << end_msg << white_fg << std::endl;
  std::cout << "|Passed Cases  |" << test_case_succeed_num_ << std::endl;
  std::cout << "|Un-Passed Case|" << test_case_failed_num_ << std::endl;
}

void UnitTest::DisplayResult(const char* test_case_name, size_t passed,
                             size_t failed, bool result) {
  std::string result_str = "PASSED";
  if (result) {
    result_str = "UN-PASSED";
  }
  std::cout << "+----------------------+" << std::endl;
  std::cout << "|TestCaseName|" << test_case_name << std::endl;
  std::cout << "+----------------------+" << std::endl;
  std::cout << "|TestResult  |" << result_str << std::endl;
  std::cout << "+----------------------+" << std::endl;
  std::cout << "|Success     |" << green_fg << passed << white_fg << std::endl;
  std::cout << "+----------------------+" << std::endl;
  std::cout << "|Failure     |" << red_fg << failed << white_fg << std::endl;
  std::cout << "+----------------------+" << std::endl;
}