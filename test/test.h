/*! @file
*********************************************************************
<PRE>
ģ����		: ���Կ��
�ļ���		: test.h
����ļ�		: test.cpp
�ļ�ʵ�ֹ���	: �����˲��԰�������Ԫ���Կ���ࣻ�ṩ��һϵ�����ڲ��Եĺ�
����			: �ɴ���Pstar
�汾			: 1.1
---------------------------------------------------------------------
���̰߳�ȫ�� : -
�쳣ʱ��ȫ�� : -
---------------------------------------------------------------------
��ע			: 
	1��UnitTest��һ���󼯺ϣ�ʹ�õ���ģʽ����֤�������ظ���UnitTest������
��������TestCase��ͨ�����ʵ�ֹ��ܵ��ӡ�
	2�����Կ����Ҫ���ڲ����㷨��������������д��
---------------------------------------------------------------------
�޸ļ�¼	:
�� ��			�汾		�޸���		�޸�����
2020/04/27		1.0		�ɴ���Pstar	����
2020/04/28		1.1		�ɴ���Pstar	�޸Ĳ����������ӱȽ϶���
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
	const char* _Case_Name;	//���԰�������
	bool		_Result;	//���԰���ִ�н��
	double		_Macro_Failed;	//���԰����к����ʧ�ܸ���
	double		_Macro_Passed;	//���԰����к���Գɹ�����
};


class UnitTest 
{
public:
	static UnitTest* GetInstance();
	TestCase* RegisterTestCase(TestCase* testcase);
	void Run();
	
public:
	TestCase*	_Cur_TestCase;
	double		_TestCase_Passed;		//���԰���ͨ����
	double		_TestCase_Failed;		//���԰���ʧ����
protected:
	std::vector<TestCase*> _All_TestCase;	//������еĲ��԰���
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
//ʹ�ú궨���ڸǸ��ӵķ�װ����

//�������е��㷨���ԣ������������
#define RUN_ALL_TESTS() \
TinySTL::test::UnitTest::GetInstance()->Run()

//TEST(A)չ����
//��������һ��A_TEST���࣬Ȼ�󴴽�һ��������ӵ�������_All_TestCase��
//		TEST(A)
//		{
//			....
//		}
//�������������ֱ�ӳ�ΪTestCase��Run()����麯���ĺ����壬����������д
#define TEST(_Name) \
STL_TEST(_Name)


//��_Name�滻��_Name_TEST
#define TESTCASE_NAME(_Name) \
_Name##_TEST

//ͨ���궨����ʵ��һ���࣬�̳�TestCase,��Ҫ��Ϊ����дRun����
//TESTCASE_NAME(_Name) ��������
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
//	���ڲ��Եĺ궨��
//	EXPECT_* ϵ�ж��ԣ�������ʧ��ʱ����������ִ��


//	1������ٶ���
//	EXPECT_TRUE(Condition)	ͨ������ΪConditionΪtrue
//	EXPECT_FALSE(Condition)	ͨ������ΪConditionΪfalse
//	���ӣ�
//	bool isPrime(int n); �ж�Ϊ����
//	EXPECT_TRUE(isPrime(2));	ͨ��
//	EXPECT_TRUE(isPrime(6));	ʧ��
//	EXPECT_FALSE(isPrime(2));	ʧ��
//	EXPECT_FALSE(isPrime(6));	ͨ��

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



//	2�����Ƚ϶���
//	EXPECT_EQ(val1,val2)	ͨ������Ϊval1==val2
//	EXPECT_NE(val1,val2)	ͨ������Ϊval1!=val2
//	EXPECT_LT(val1,val2)	ͨ������Ϊval1<val2
//	EXPECT_LE(val1,val2)	ͨ������Ϊval1<=val2
//	EXPECT_GT(val1,val2)	ͨ������Ϊval1>val2
//	EXPECT_GE(val1,val2)	ͨ������Ϊval1>=val2
//	ע�⣺
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
