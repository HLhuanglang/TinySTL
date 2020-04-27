/*! @file
*********************************************************************
<PRE>
模块名       : 内存分配器
文件名       : construct.h
相关文件     : allocator.h
文件实现功能 : 提供对象构造与析构功能函数
作者         : 派大星Pstar
版本         : 1.0
---------------------------------------------------------------------
多线程安全性 : 否，暂未考虑
异常时安全性 : 否，
---------------------------------------------------------------------
备注         : 
---------------------------------------------------------------------
修改记录 :
日 期        版本     修改人            修改内容
2020/04/27   1.0   派大星Pstar			 创建
</PRE>
********************************************************************/


#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include"type_traits.h"
#include"exceptdef.h"
#include<new>  //for placement new

namespace TinySTL {
	
template<typename T1>
inline void construct(IN T1* _Ptr) 
{
	new(_Ptr) T1();
}
	
template<typename T1, typename T2>
inline void construct(IN T1 *_Ptr, IN const T2& _Val) 
{
	new(_Ptr) T1(_Val);
}
	
template<typename T>
inline void destory(IN T *_Ptr) 
{
	_Ptr->~T();
}

template<typename _InIt>
inline void destory(IN _InIt _First,IN _InIt _Last)
{
	typedef typename __type_traits<_InIt>::is_POD_type		IS_POD_TYPE;
	Pstar_destory(_First, _Last, IS_POD_TYPE()/*括号可以省略*/);
}

template<typename _InIt>
inline void Pstar_destory(IN _InIt _First, IN _InIt _Last, DUMMY __true_type _True) 
{
	//内置类型，析构与否都无所谓，所以不做处理
}

template<typename _InIt>
inline void Pstar_destory(IN _InIt _First, IN _InIt _Last, DUMMY __false_type _False) 
{	//不是内置类型，属于用户自定义类型，需要析构释放资源
	while (_First != _Last)
	{
		destory(&*_First); //*_First取得内容，再用&取得地址
		++_First;
	}
}

} //namespace TinySTL
#endif // !CONSTRUCT_H

