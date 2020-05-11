/*! @file
*********************************************************************
<PRE>
模块名		: 测试框架
文件名		: test.h
相关文件		: test.cpp
文件实现功能	: 定义了测试案例、单元测试框架类；提供了一系列用于测试的宏
作者			: 派大星Pstar
版本			: 1.1
---------------------------------------------------------------------
多线程安全性 : -
异常时安全性 : -
---------------------------------------------------------------------
备注			: 
	1、UnitTest是一个大集合，使用单例模式，保证案例不重复，UnitTest包括很
多个具体的TestCase，通过组合实现功能叠加。
	2、测试框架主要用于测试算法，针对容器则按需编写。
---------------------------------------------------------------------
修改记录	:
日 期			版本		修改人		修改内容
2020/04/27		1.0		派大星Pstar	创建
2020/04/28		1.1		派大星Pstar	修改参数名，增加比较断言
</PRE>
********************************************************************/
#ifndef TEST_H
#define TEST_H
#include"lib/redbud/io/color.h"

#include<ctime>
#include<vector>

namespace TinySTL {
namespace test {
#define green redbud::io::state::manual<<redbud::io::hfg::green
#define red redbud::io::state::manual<<redbud::io::hfg::red
}//test namespace

namespace test {

class TestCase 
{
public:
	TestCase(const char* name)
		: _Case_Name(name) 
	{
	}
	virtual void Run() = 0;
	
public:
	const char* _Case_Name;	//测试案例名称
	bool		_Result;	//测试案例执行结果
	double		_Macro_Failed;	//测试案例中宏断言失败个数
	double		_Macro_Passed;	//测试案例中宏断言成果个数
};


class UnitTest 
{
public:
	static UnitTest* GetInstance();
	TestCase* RegisterTestCase(TestCase* testcase);
	void Run();
	
public:
	TestCase*	_Cur_TestCase;
	double		_TestCase_Passed;		//测试案例通过数
	double		_TestCase_Failed;		//测试案例失败数
protected:
	std::vector<TestCase*> _All_TestCase;	//存放所有的测试案例
};


UnitTest* UnitTest::GetInstance()
{	
	static UnitTest _Instance;
	return &_Instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase)
{
	_All_TestCase.push_back(testcase);
	return testcase;
}

void UnitTest::Run()
{

}


/********************************************************************************************************/
//使用宏定义掩盖复杂的封装过程

//开启所有的算法测试，容器单独设计
#define RUN_ALL_TESTS() \
TinySTL::test::UnitTest::GetInstance()->Run()

//TEST(A)展开后
//会先生成一个A_TEST的类，然后创建一个对象，添加到单例的_All_TestCase中
//		TEST(A)
//		{
//			....
//		}
//花括号里的内容直接成为TestCase的Run()这个虚函数的函数体，这就完成了重写
#define TEST(_Name) \
STL_TEST(_Name)


//将_Name替换成_Name_TEST
#define TESTCASE_NAME(_Name) \
_Name##_TEST

//通过宏定义来实现一个类，继承TestCase,主要是为了重写Run方法
//TESTCASE_NAME(_Name) 就是类名
#define STL_TEST(_Name)	\
class TESTCASE_NAME(_Name) : public TestCase {	\
public:	\
TESTCASE_NAME(_Name)(const char* _Case_Name)	\
    : _Case_Name(_Case_Name)	\
	{	\
	};	\
virtual void Run();	\
private:	\
static TestCase* const testcase_;	\
};	\
\
TestCase* const TESTCASE_NAME(_Name)	\
::testcase_ = UnitTest::GetInstance()->RegisterTestCase(  \
    new TESTCASE_NAME(_Name)(#_Name));    \
void TESTCASE_NAME(_Name)::Run()




/********************************************************************************************************/
//	用于测试的宏定义
//	EXPECT_* 系列断言，当检查点失败时，继续往下执行


//	1——真假断言
//	EXPECT_TRUE(Condition)	通过条件为Condition为true
//	EXPECT_FALSE(Condition)	通过条件为Condition为false
//	例子：
//	bool isPrime(int n); 判断为素数
//	EXPECT_TRUE(isPrime(2));	通过
//	EXPECT_TRUE(isPrime(6));	失败
//	EXPECT_FALSE(isPrime(2));	失败
//	EXPECT_FALSE(isPrime(6));	通过

#define EXPECT_TRUE(Condition) do{\
if(Condition){	\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Passed++;	\
	std::cout<<green<<"EXPECT_TRUE succeeded\n";	\
}else{	\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Failed++;	\
	UnitTest::GetInstance()->_Cur_TestCase->_Result = false;	\
	std::cout<<red<<"EXPECT_TRUE failed!\n";				\
}}while(0)

#define EXPECT_FALSE(Condition) do {\
if(!Condition){	\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Passed++;	\
	std::cout<<green<<"EXPECT_FALSE succeeded\n";	\
}else{	\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Failed++;	\
	UnitTest::GetInstance()->_Cur_TestCase->_Result = false;	\
	std::cout<<red<<"EXPECT_FALSE failed!\n";	\
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

#define EXPECT_EQ(val1, val2)	do{	\
if(val1 == val2){\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Passed++;	\
	std::cout << green << "EXPECT_EQ succeeded\n";	\
}else {\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Failed++;	\
	UnitTest::GetInstance()->_Cur_TestCase->_Result = false;	\
	std::cout<<red<<"EXPECT_EQ failed!\n";	\
	std::cout<<red<<"EXPECTED_VALUE:"<<val1<<std::endl;	\
	std::cout<<red<<"ACTUAL_VALUE:"<<val2<<std::endl;	\
}}while(0)


#define EXPECT_NE(val1, val2)	do{\
if(val1!=val2){\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Passed++;	\
	std::cout<<green<<"EXPECT_NE succeeded\n";	\
}else{\
	UnitTest::GetInstance()->_Cur_TestCase->_Macro_Failed++;	\
	UnitTest::GetInstance()->_Cur_TestCase->_Result = false;	\
}}while(0)



} //namespace test
}// namespace TinySTL
#endif // !TEST_H
