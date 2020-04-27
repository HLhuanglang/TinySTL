/*! @file
*********************************************************************
<PRE>
ģ����       : �ڴ������
�ļ���       : allocator.h
����ļ�     : alloc.h
�ļ�ʵ�ֹ��� : �ṩ�������࣬ʵ���ڴ��������ͷš������������Ĺ���
����         : �ɴ���Pstar
�汾         : 1.0
---------------------------------------------------------------------
���̰߳�ȫ�� : <��/��>[��˵��]
�쳣ʱ��ȫ�� : <��/��>[��˵��]
---------------------------------------------------------------------
��ע         : <����˵��>
---------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���              �޸�����
2020/4/27   1.0      �ɴ���Pstar			  ����
</PRE>
********************************************************************/


#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include"alloc.h"
#include"construct.h"
#include"exceptdef.h"

#include<new>
namespace TinySTL {
/*! @class
*******************************************************************************
<PRE>
������   : allocator.h
����     : �ṩ�ڴ��������ͷš������������Ĺ���
�쳣��   : ��
-------------------------------------------------------------------------------
��ע     : �ڴ����뺯�������ǡ����������
�����÷� :
	using data_allocator = TinySTL::allocator<T>
	data_allocator::<���庯��>
-------------------------------------------------------------------------------
����     : �ɴ���Pstar
</PRE>
******************************************************************************/
template<typename T>
class allocator 
{
public:
	//��дҲ�ǿ��Եģ�ֻ�ǹ���ͳһ�������ͱ𣬷������Ϳɶ���
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using const_reference = const T&;
	using const_pointer = const T*;
public:
	static T* allocate();	//����һ�������С���ڴ�
	static T* allocate(IN size_t _Count);	//����_Count�������С���ڴ�
	static void deallocate(IN T* _Ptr);	//�ͷ�_Ptrָ���һ�������С���ڴ�
	static void deallocate(IN T* _Ptr, IN size_t _Count);	//�ͷ�_Ptrָ���_Count�������С���ڴ�

	static void construct(IN T* _Ptr);	//��_Ptrָ���λ�ù�����󣬶���ֵĬ��
	static void construct(IN T* _Ptr, IN const T& _Val);	//��_Ptrָ���λ�ù�����󣬶���ֵΪ_Val
	static void destory(IN T* _Ptr);	//����_Ptrָ����ڴ棬Ĭ��һ�������С
	static void destory(IN T* _First, IN T* _Last);	//����[_First,_Last]��Χ�ڶ���
};//end of class allocator

template<typename T>
T* allocator<T>::allocate() 
{	/*�����ڴ��СΪһ�������С*/
	return static_cast<T*>(TinySTL::alloc::allocate(sizeof(T)));
}

template<typename T>
T* allocator<T>::allocate(IN size_t _Count)
{
	if (_Count == 0) {
		std::cerr << "�����ڴ������0";
	}
	return static_cast<T*>(TinySTL::alloc::allocate(_Count * sizeof(T)));
}

template<typename T>
void allocator<T>::deallocate(IN T* _Ptr)
{
	TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T));
}

template<typename T>
void allocator<T>::deallocate(IN T* _Ptr, IN size_t _Count)
{
	if (_Count == 0){
		return;
	} 
	TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T)*_Count);
}

template<typename T>
void allocator<T>::construct(IN T* _Ptr)
{
	TinySTL::construct(_Ptr);
}

template<typename T>
void allocator<T>::construct(IN T* _Ptr, IN const T& _Val)
{
	TinySTL::construct(_Ptr, _Val);
}

template<typename T>
void allocator<T>::destory(IN T* _Ptr)
{
	TinySTL::destory(_Ptr);
}

template<typename T>
void allocator<T>::destory(IN T* _First, IN T* _Last)
{
	for (; _First != _Last; ++_First) {
		TinySTL::destory(_First);
	}
}
} //namespace TinySTL
#endif // !ALLOCATOR_H

