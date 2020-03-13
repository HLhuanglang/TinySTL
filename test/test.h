#ifndef TEST_H
#define TEST_H
#include<vector>
namespace TinySTL {
	
	class TestCase {
	public:
		TestCase(const char* name) : testcase_name(name) {}
		virtual void run() = 0;
	public:
		const char* testcase_name;
		int nTestResult;
	};

	class UnitTest {
	public:
		static UnitTest* GetInstance();
		TestCase* RegisterTestCase(TestCase* testcase);
		int Run();
	public:
		int nTestResult;
		int nPassed;
		int nFailed;
		TestCase* CurrentTestCase;
	protected:
		std::vector<TestCase*> testcases;
	};




}// namespace TinySTL
#endif // !TEST_H
