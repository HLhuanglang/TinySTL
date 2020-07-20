/*********************************************************************
模块名		: 内存分配器
文件名		: construct.h
相关文件		: allocator.h
文件实现功能	: 提供对象构造与析构功能函数
作者			: HLhuanglang
版本			: 1.0
---------------------------------------------------------------------
多线程安全性 : 否，暂未考虑
异常时安全性 : 否，
---------------------------------------------------------------------
备注			: 
---------------------------------------------------------------------
修改记录		:
日 期		版本		修改人			修改内容
2020/04/27	1.0		HLhuanglang		创建
********************************************************************/
#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include"type_traits.h"
#include"exceptdef.h"

#include<new>  //for placement new

namespace TinySTL {
/******************************************************
函 数 名	：construct
函数作用	：在_Ptr处构造对象
函数参数	：
		[IN]	_Ptr:指向目标内存地址的指针
返 回 值	：无
******************************************************/
template<typename _Ty1>
inline void construct(IN _Ty1* _Ptr) 
{
	new(_Ptr) _Ty1();
}


/******************************************************
函 数 名	：construct
函数作用	：在_Ptr处构造对象,对象值为_Val
函数参数	：
		[IN]	_Ptr:指向目标内存地址的指针
返 回 值	：无
******************************************************/
template<typename _Ty1, typename _Ty2>
inline void construct(IN _Ty1 *_Ptr, IN const _Ty2& _Val) 
{
	new(_Ptr) _Ty1(_Val);
}



/******************************************************
函 数 名	：destory
函数作用	：在_Ptr析构对象 
函数参数	：
		[IN]	_Ptr:指向目标内存地址的指针
返 回 值	：无
******************************************************/
template<typename _Ty1>
inline void destory(IN _Ty1 *_Ptr) 
{
	_Ptr->~_Ty1();
}



/******************************************************
函 数 名	：destory
函数作用	：析构[_First, _Last)区间内的对象
函数参数	：
		[IN]	_First:目标区间起始地址
		[IN]	_Last :目标区间结束地址
返 回 值	：无
******************************************************/
template<typename _InIt>
inline void destory(IN _InIt _First, IN _InIt _Last)
{
	typedef typename __type_traits<_InIt>::is_POD_type	IS_POD_TYPE;
	_destory(_First, _Last, IS_POD_TYPE());
}

template<typename _InIt>
inline void _destory( _InIt _First,  _InIt _Last,  __true_type _True)
{
	//内置类型，析构与否都无所谓，所以不做处理
}

template<typename _InIt>
inline void _destory( _InIt _First,  _InIt _Last,  __false_type _False)
{	//不是内置类型，属于用户自定义类型，需要析构释放资源
	while (_First != _Last)
	{
		destory(&*_First); //*_First取得内容，再用&取得地址
		++_First;
	}
}

} //namespace TinySTL
#endif // !CONSTRUCT_H

