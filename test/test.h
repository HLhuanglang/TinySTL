#ifndef TEST_H
#define TEST_H

#include"../3rd/lib/redbud/io/color.h"

#include<ctime>
#include<vector>

namespace TinySTL {
namespace test {
#define green redbud::io::state::manual<<redbud::io::hfg::green
#define red redbud::io::state::manual<<redbud::io::hfg::red
}//test namespace

namespace test {

	class TestCase {
	public:
		TestCase(const char* name) : testcase_name(name) {}
		virtual void Run() = 0;
	
	public:
		const char* testcase_name;	//测试案例名称
		int nTestResult;	//测试案例执行结果	1:通过 0：失败
		double nFailed;		//测试案例失败数
		double nPassed;		//测试案例通过数
	};

	class UnitTest {
	public:
		static UnitTest* GetInstance();
		TestCase* RegisterTestCase(TestCase* testcase);
		void Run();
	
	public:
		TestCase* CurrentTestCase;
		double nPassed;
		double nFailed;
	protected:
		std::vector<TestCase*> _testcases;
	};

	UnitTest* UnitTest::GetInstance()
	{	
		static UnitTest _Instance;	//静态局部变量
		return &_Instance;
	}

	TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
	{
		_testcases.push_back(testcase);
		return testcase;
	}

	void UnitTest::Run()
	{
		for (auto it : _testcases) {
			TestCase *testcase = it;
			CurrentTestCase = testcase;
			testcase->nTestResult = 1;
			testcase->nFailed = 0;
			testcase->nPassed = 0;
			std::cout << green << "============================================\n";
			std::cout << green << "Run TestCase:" << testcase->testcase_name << "\n";
			testcase->Run();
			if (testcase->nFailed == 0)
				std::cout << green;
			else
				std::cout << red;
			std::cout << " " << testcase->nPassed << " / " << testcase->nFailed + testcase->nPassed
				<< " Cases passed. ( " << testcase->nPassed /
				(testcase->nFailed + testcase->nPassed) * 100 << "% )\n";
			std::cout << green << "End TestCase:" << testcase->testcase_name << "\n";
			if (testcase->nTestResult)
				++nPassed;
			else
				++nFailed;
		}
		std::cout << green << "============================================\n";
		std::cout << green << " Total TestCase : " << nPassed + nFailed << "\n";
		std::cout << green << " Total Passed : " << nPassed << "\n";
		std::cout << red << " Total Failed : " << nFailed << "\n";
		std::cout << green << " " << nPassed << " / " << nFailed + nPassed
			<< " TestCases passed. ( " << nPassed / (nFailed + nPassed) * 100 << "% )\n";
	}


/********************************************************************************************************/
//使用宏定义掩盖复杂的封装过程

//开启所有的算法测试，容器单独设计
#define RUN_ALL_TESTS() \
	TinySTL::test::UnitTest::GetInstance()->Run()

//将testcase_name替换成testcase_name_TEST
#define TESTCASE_NAME(testcase_name) \
	testcase_name##_TEST

//通过宏定义来实现一个类，继承TestCase
#define STL_TEST(testcase_name)								  \
class TESTCASE_NAME(testcase_name) : public TestCase {        \
public:                                                       \
    TESTCASE_NAME(testcase_name)(const char* case_name)       \
        : TestCase(case_name) {};                             \
    virtual void Run();                                       \
private:                                                      \
    static TestCase* const testcase_;                         \
};                                                            \
                                                              \
TestCase* const TESTCASE_NAME(testcase_name)                  \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase(  \
        new TESTCASE_NAME(testcase_name)(#testcase_name));    \
void TESTCASE_NAME(testcase_name)::Run()


//TEST(A)展开后
//会先生成一个A_TEST的类，然后创建一个对象，添加到单例的_testcase集合中
//		TEST(A)
//		{
//			....
//		}
//花括号里的内容直接成为Run()这个虚函数的函数体，这就完成了重写
#define TEST(testcase_name) \
	STL_TEST(testcase_name)



/********************************************************************************************************/
//用于测试的宏定义
// EXPECT_* 系列断言，当检查点失败时，继续往下执行


//	1——真假断言
//	EXPECT_TRUE(Condition)	通过条件为Condition为true
//	EXPECT_FALSE(Condition)	通过条件为Condition为false
//	例子：
//	bool isPrime(int n); 判断为素数
//	EXPECT_TRUE(isPrime(2));	通过
//	EXPECT_TRUE(isPrime(6));	失败
//	EXPECT_FALSE(isPrime(2));	失败
//	EXPECT_FALSE(isPrime(6));	通过

#define EXPECT_TRUE(Condition) do {								\
	if(Condition){												\
		UnitTest::GetInstance()->CurrentTestCase->nPassed++;	\
		std::cout<<green<<"EXPECT_TRUE succeeded\n";			\
	}else{														\
		UnitTest::GetInstance()->CurrentTestCase->nTestResult=0;\
		UnitTest::GetInstance()->CurrentTestCase->nFailed++;	\
		std::cout<<red<<"EXPECT_TRUE failed!\n";				\
	}}while(0)

#define EXPECT_FALSE(Condition) do {							\
	if(!Condition){												\
		UnitTest::GetInstance()->CurrentTestCase->nPassed++;	\
		std::cout<<green<<"EXPECT_FALSE succeeded\n";			\
	}else{														\
		UnitTest::GetInstance()->CurrentTestCase->nTestResult=0;\
		UnitTest::GetInstance()->CurrentTestCase->nFailed++;	\
		std::cout<<red<<"EXPECT_FALSE failed!\n";				\
	}}while(0)



//	2——比较断言
//	EXPECT_EQ(val1,val2)	通过条件为val1==val2
//	EXPECT_NE(val1,val2)	通过条件为val1!=val2
//	EXPECT_LT(val1,val2)	通过条件为val1<val2
//	EXPECT_LE(val1,val2)	通过条件为val1<=val2
//	EXPECT_GT(val1,val2)	通过条件为val1>val2
//	EXPECT_GE(val1,val2)	通过条件为val1>=val2
//	注意：
//	EXPECT_*(expected, actual)

} //namespace test
}// namespace TinySTL
#endif // !TEST_H
