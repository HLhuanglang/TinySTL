/*! @file
*********************************************************************
<PRE>
模块名       : 内存分配器
文件名       : allocator.h
相关文件     : alloc.h
文件实现功能 : 提供分配器类，实现内存申请与释放、对象构造与消耗功能
作者         : 派大星Pstar
版本         : 1.0
---------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
---------------------------------------------------------------------
备注         : <其它说明>
---------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
2020/4/27   1.0      派大星Pstar			  创建
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
类名称   : allocator.h
功能     : 提供内存申请与释放、对象构造与消耗功能
异常类   : 无
-------------------------------------------------------------------------------
备注     : 内存申请函数参数是‘对象个数’
典型用法 :
	using data_allocator = TinySTL::allocator<T>
	data_allocator::<具体函数>
-------------------------------------------------------------------------------
作者     : 派大星Pstar
</PRE>
******************************************************************************/
template<typename T>
class allocator 
{
public:
	//不写也是可以的，只是构建统一的类型型别，方便管理和可读性
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using const_reference = const T&;
	using const_pointer = const T*;
public:
	static T* allocate();	//申请一个对象大小的内存
	static T* allocate(IN size_t _Count);	//申请_Count个对象大小的内存
	static void deallocate(IN T* _Ptr);	//释放_Ptr指向的一个对象大小的内存
	static void deallocate(IN T* _Ptr, IN size_t _Count);	//释放_Ptr指向的_Count个对象大小的内存

	static void construct(IN T* _Ptr);	//在_Ptr指向的位置构造对象，对象值默认
	static void construct(IN T* _Ptr, IN const T& _Val);	//在_Ptr指向的位置构造对象，对象值为_Val
	static void destory(IN T* _Ptr);	//析构_Ptr指向的内存，默认一个对象大小
	static void destory(IN T* _First, IN T* _Last);	//析构[_First,_Last]范围内对象
};//end of class allocator

template<typename T>
T* allocator<T>::allocate() 
{	/*申请内存大小为一个对象大小*/
	return static_cast<T*>(TinySTL::alloc::allocate(sizeof(T)));
}

template<typename T>
T* allocator<T>::allocate(IN size_t _Count)
{
	if (_Count == 0) {
		std::cerr << "申请内存需大于0";
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

