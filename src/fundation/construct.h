/**************************************************************
���ƣ�construct.h
���ã��������Ĺ��������
**************************************************************/

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include"type_traits.h"
#include<new>  //for placement new

namespace TinySTL {
	
	template<typename T1>
	inline void construct(T1* pointer) {
		new(pointer) T1();
	}
	
	template<typename T1, typename T2>
	inline void construct(T1 *pointer, const T2& value) {
		new(pointer) T1(value);
	}
	
	template<typename T>
	inline void destory(T *pointer) {
		pointer->~T();
	}

	template<typename InputIterator>
	inline void _destory(InputIterator first, InputIterator last, __true_type) {
		//�������ͣ������������ν�����Բ�������
	}

	template<typename InputIterator>
	inline void _destory(InputIterator first, InputIterator last, __false_type) {
		//�����������ͣ������û��Զ������ͣ���Ҫ�����ͷ���Դ
		while (first != last)
		{
			destory(&*first); //��Ϊ����������ָ�룬*firstȡ�����ݣ�����&ȡ�õ�ַ
			++first;
		}
	}

	template<typename InputIterator>
	inline void destory(InputIterator firsrt, InputIterator last) {
		typedef typename __type_traits<InputIterator>::is_POD_type		IS_POD_TYPE;
		_destory(firsrt, last, IS_POD_TYPE);
	}

} //namespace TinySTL
#endif // !CONSTRUCT_H

