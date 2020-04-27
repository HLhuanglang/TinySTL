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
		const char* testcase_name;	//���԰�������
		int nTestResult;	//���԰���ִ�н��	1:ͨ�� 0��ʧ��
		double nFailed;		//���԰���ʧ����
		double nPassed;		//���԰���ͨ����
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
		static UnitTest _Instance;	//��̬�ֲ�����
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
//ʹ�ú궨���ڸǸ��ӵķ�װ����

//�������е��㷨���ԣ������������
#define RUN_ALL_TESTS() \
	TinySTL::test::UnitTest::GetInstance()->Run()

//��testcase_name�滻��testcase_name_TEST
#define TESTCASE_NAME(testcase_name) \
	testcase_name##_TEST

//ͨ���궨����ʵ��һ���࣬�̳�TestCase
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


//TEST(A)չ����
//��������һ��A_TEST���࣬Ȼ�󴴽�һ��������ӵ�������_testcase������
//		TEST(A)
//		{
//			....
//		}
//�������������ֱ�ӳ�ΪRun()����麯���ĺ����壬����������д
#define TEST(testcase_name) \
	STL_TEST(testcase_name)



/********************************************************************************************************/
//���ڲ��Եĺ궨��
// EXPECT_* ϵ�ж��ԣ�������ʧ��ʱ����������ִ��


//	1������ٶ���
//	EXPECT_TRUE(Condition)	ͨ������ΪConditionΪtrue
//	EXPECT_FALSE(Condition)	ͨ������ΪConditionΪfalse
//	���ӣ�
//	bool isPrime(int n); �ж�Ϊ����
//	EXPECT_TRUE(isPrime(2));	ͨ��
//	EXPECT_TRUE(isPrime(6));	ʧ��
//	EXPECT_FALSE(isPrime(2));	ʧ��
//	EXPECT_FALSE(isPrime(6));	ͨ��

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



//	2�����Ƚ϶���
//	EXPECT_EQ(val1,val2)	ͨ������Ϊval1==val2
//	EXPECT_NE(val1,val2)	ͨ������Ϊval1!=val2
//	EXPECT_LT(val1,val2)	ͨ������Ϊval1<val2
//	EXPECT_LE(val1,val2)	ͨ������Ϊval1<=val2
//	EXPECT_GT(val1,val2)	ͨ������Ϊval1>val2
//	EXPECT_GE(val1,val2)	ͨ������Ϊval1>=val2
//	ע�⣺
//	EXPECT_*(expected, actual)

} //namespace test
}// namespace TinySTL
#endif // !TEST_H
