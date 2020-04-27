/*! @file
*********************************************************************
<PRE>
模块名       : 通用
文件名       : uninitialized.h
相关文件     : type_traits.h、iterator.h、
文件实现功能 : 提供通用的内存处理函数
作者         : 派大星Pstar
版本         : 1.0
---------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
---------------------------------------------------------------------
备注         : -
---------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
2020/4/27    1.0     派大星Pstar			   创建
</PRE>
********************************************************************/

#ifndef UNINITIALIZED_H
#define UNINITIALIZED_H

#include"type_traits.h"
#include"construct.h"
#include"iterator.h"
#include"exceptdef.h"
#include"../algorithm/algorithm.h"

#include<cstring>
namespace TinySTL {
/*! @function
********************************************************************************
<PRE>
函数名   : uninitialized_copy
功能     : 将范围(_First, _Last]内元素复制到_Result位置
参数     : 
		   [IN]		_First  : 给定范围的起始迭代器
		   [IN]		_Last   : 给定范围的结束迭代器
		   [IN/OUT] _Result	: IN-目标区间的起始迭代器,OUT-目标区间的结束位置
返回值   : 返回新区间的 ‘结束迭代器’，即 _Result+(_Last-_Fistr)处迭代器
抛出异常 : 
		   bad_alloc : 可能new失败.（几率很小）
-------------------------------------------------------------------------------
复杂度   : -
备注     : -
典型用法 : -
-------------------------------------------------------------------------------
作者     : 派大星Pstar
</PRE>
*******************************************************************************/
template<typename _InIt, typename _FwdIt>
_FwdIt uninitialized_copy(IN _InIt _First, IN _InIt _Last, IN OUT _FwdIt _Result)
{
	typedef typename __type_traits<iterator_traits<_FwdIt>::value_type>::is_POD_type		IS_POD_TYPE;
	return Pstar_uninitialized_copy_aux(_First, _Last, _Result, IS_POD_TYPE());
}

template<typename _InIt, typename _FwdIt>
_FwdIt Pstar_uninitialized_copy_aux(IN _InIt _First, IN _InIt _Last,
	IN OUT _FwdIt _Result, DUMMY __true_type)
{
	memcpy(_Result, _First, (_Last - _First) * sizeof(*_First));
	return _Result + (_Last - _First);
}

template<typename _InIt, typename _FwdIt>
_FwdIt Pstar_uninitialized_copy_aux(IN _InIt _First, IN _InIt _Last,
	IN OUT _FwdIt _Result, DUMMY __false_type)
{
	_FwdIt _Tmp = _Result;
	try
	{
		for (; _First != _Last; ++_First, ++_Tmp)
			TinySTL::construct(&*_Tmp, *_First);	/*可能抛出bad_alloc异常*/
	}
	catch (...)
	{
		for (; _Result != _Tmp; ++_Result)
			TinySTL::destory(&*++_Result);
	}
	return _Tmp;
}


/*! @function
********************************************************************************
<PRE>
函数名   : uninitialized_fill
功能     : 对范围(_First, _Last]进行对象填充，对象值为_val
参数     :
		   [IN]		_First  : 给定范围的起始迭代器
		   [IN]		_Last   : 给定范围的结束迭代器
		   [IN]		_Val	: 填充对象的值
返回值   : 无
抛出异常 : -
-------------------------------------------------------------------------------
复杂度   : -
备注     : -
典型用法 : -
-------------------------------------------------------------------------------
作者     : 派大星Pstar
</PRE>
*******************************************************************************/
template<typename _FwdIt, typename T>
void uninitialized_fill(IN _FwdIt _First, IN _FwdIt _Last, IN const T& _Val)
{
	typedef typename __type_traits<T>::is_POD_type		IS_POD_TYPE;
	Pstar_uninitialized_fill_aux(_First, _Last, _Val, IS_POD_TYPE());
}

template<typename _FwdIt,typename T>
void Pstar_uninitialized_fill_aux(IN _FwdIt _First, IN _FwdIt _Last, IN const T& _Val, DUMMY __true_type)
{
	TinySTL::fill(_First, _Last, _Val);
}
template<typename _FwdIt, typename T>
void Pstar_uninitialized_fill_aux(IN _FwdIt _First, IN _FwdIt _Last, IN const T& _Val, DUMMY __false_type)
{
	for (; _First != _Last; ++_First)
		TinySTL::construct(_First, _Val);
}


/*! @function
********************************************************************************
<PRE>
函数名   : uninitialized_fill_n
功能     : 从_First起始迭代器位置进行_Count个对象填充，对象值为_val
参数     :
		   [IN/OUT]	_First  : IN-目标位置起始迭代器,OUT-填充结束处迭代器
		   [IN]		_Count  : 填充对象个数
		   [IN]		_Val	: 填充对象的值
返回值   : 返回填充结束位置处迭代器，即_First+sizeof(T)*_Count处迭代器
抛出异常 : -
-------------------------------------------------------------------------------
复杂度   : -
备注     : -
典型用法 : -
-------------------------------------------------------------------------------
作者     : 派大星Pstar
</PRE>
*******************************************************************************/
template<typename _FwdIt, typename Size, typename T>
_FwdIt uninitialized_fill_n(IN OUT _FwdIt _First, IN Size _Count, IN const T& _Val) {
	typedef typename __type_traits<iterator_traits<_FwdIt>::value_type>::is_POD_type		IS_POD_TYPE;
	return Pstar_uninitialized_fill_n_aux(_First, _Count, _Val, IS_POD_TYPE());
}

template<typename _FwdIt, typename Size,typename T>
_FwdIt Pstar_uninitialized_fill_n_aux(IN OUT _FwdIt _First, IN Size _Count, 
	IN const T& _Val, DUMMY __true_type)
{
	return TinySTL::fill_n(_First, _Count, _Val);
}

template<typename _FwdIt , typename Size, typename T>
_FwdIt Pstar_uninitialized_fill_n_aux(IN OUT _FwdIt _First, IN Size _Count, 
	IN const T& _Val, DUMMY __false_type)
{
	Size _Tmp = _Count;
	try
	{
		for (; _Tmp > 0; _Tmp--, _First++)
			TinySTL::construct(&*_First, _Val);
	}
	catch (...)
	{
		for (; _Tmp != _Count; _Tmp++, _First--)
			TinySTL::destory(&*_First);
	}
	return _First;
}

} //namespace TinySTL
#endif // !UNINITIALIZED_H
