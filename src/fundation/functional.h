/*
���ƣ�functional.h
ע�⣺
	�������Ų�����()����const���α�ʾ������ĺ��������״̬
*/
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

namespace TinySTL {

	//����һԪ�����Ĳ����ͱ�ͷ���ֵ�ͱ�
	template<class Arg, class Result>
	struct unarg_function
	{
		typedef Arg		argument_type;
		typedef Result		result_type;
	};

	//���ڳ��ֶ�Ԫ�����ĵ�һ�����ͱ𡢵ڶ������ͱ��Լ�����ֵ�ͱ�
	template<class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1		first_argument_type;
		typedef Arg2		second_argument_type;
		typedef Result		result_type;
	};


	/*******************************************������º���**********************************/
	//�������󣺼ӷ� plus<T>
	template<class T>
	struct plus : public binary_function<T, T, T> {
		T operator()(const T&x, const T& y) const { return x + y; }
	};
	//�������󣺼���minus<T>
	template<class T>
	struct minus : public binary_function<T, T, T> {
		T operator()(const T&x, const T& y) const { return x - y; }
	};
	//�������󣺳˷�multiples<T>
	template<class T>
	struct multiplies : public binary_function<T, T, T> {
		T operator()(const T&x, const T& y) const { return x*y; }
	};	
	//�������󣺳���divides<T>
	template<class T>
	struct divides : public binary_function<T, T, T> {
		T operator()(const T&x, const T& y) const { return x/y; }
	};	
	//��������ȡģmodulus<T>
	template<class T>
	struct modulus : public binary_function<T, T, T> {
		T operator()(const T&x, const T& y) const { return x%y; }
	};	
	//�������󣺷�negate<T>
	template<class T>
	struct negate : public unarg_function<T,T> {
		T operator()(const T&x ) const { return -x; }
	};


	/*******************************************��ϵ������º���**********************************/
	//�������󣺵��� equal_to
	template<class T>
	struct equal_to : public binary_function<T, T, bool> {
		bool  operator()(const T&x, const T&y) const { return x == y; }
	};
	//�������󣺲�����not_equal_to
	template<class T>
	struct not_equal_to : public binary_function<T, T, bool> {
		bool operator()(const T&x, const T&y) const { return x != y; }
	};
	// �������󣺴���greater
	template <class T>
	struct greater :public binary_function<T, T, bool>{
		bool operator()(const T& x, const T& y) const { return x > y; }
	};
	// ��������С��less
	template <class T>
	struct less :public binary_function<T, T, bool>{
		bool operator()(const T& x, const T& y) const { return x < y; }
	};
	// �������󣺴��ڵ���greater_equal
	template <class T>
	struct greater_equal :public binary_function<T, T, bool>{
		bool operator()(const T& x, const T& y) const { return x >= y; }
	};
	// ��������С�ڵ���less_equal
	template <class T>
	struct less_equal :public binary_function<T, T, bool>{
		bool operator()(const T& x, const T& y) const { return x <= y; }
	};

	/*******************************************�߼���º���**********************************/
	//���������߼�����and logical_and<T>
	template<class T>
	struct logical_and : public binary_function<T, T, bool> {
		bool operator()(const T&x, const T&y) const { return x && y; }
	};
	//���������߼�����or logical_or<T>
	template<class T>
	struct logical_or : public binary_function<T, T, bool> {
		bool operator()(const T&x, const T&y) const { return x || y; }
	};
	//���������߼�����not logical_not<T>
	template<class T>
	struct logical_not : public unarg_function<T,bool> {
		bool operator()(const T&x) const { return  !x; }
	};

} //namespace TinySYL
#endif // !FUNCTIONAL_H

