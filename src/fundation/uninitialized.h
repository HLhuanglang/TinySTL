/*********************************************************
名称：uninitialized.h
作用：提供内存处理工具函数
说明：
**********************************************************/
#ifndef UNINITIALIZED_H
#define UNINITIALIZED_H

#include"type_traits.h"
#include"construct.h"
#include"iterator.h"
#include"../algorithm/algorithm.h"

#include<cstring>
namespace TinySTL {
	/*****************************************************
	名称：uninitialized_copy
	作用：将[_First,_Last) 复制到[_Result，_Result+(_Last-_First) ),返回复制结束的位置
	*****************************************************/
	template<typename _InIt, typename _FwdIt>
	_FwdIt Pstar_uninitialized_copy_aux(_InIt _First,_InIt _Last,
		_FwdIt _Result, __true_type){
		memcpy(_Result, _First, (_Last - _First) * sizeof(*_First));
		return _Result + (_Last - _First);
	}

	template<typename _InIt, typename _FwdIt>
	_FwdIt Pstar_uninitialized_copy_aux(_InIt _First, _InIt _Last,
		_FwdIt _Result, __false_type) {
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

	template<typename _InIt, typename _FwdIt>
	_FwdIt uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Result) {
		typedef typename __type_traits<iterator_traits<_FwdIt>::value_type>::is_POD_type		IS_POD_TYPE;
		return Pstar_uninitialized_copy_aux(_First, _Last, _Result, IS_POD_TYPE());
	}


	/***********************************************************************
	名称：uninitialized_fill
	作用：对给定的范围[_First，_Last)，按值为_Val进行对象构造,无返回值
	************************************************************************/
	template<typename _FwdIt,typename T>
	void Pstar_uninitialized_fill_aux(_FwdIt _First, _FwdIt _Last, const T& _Val, __true_type) {
		//后续使用fill算法进行替换
		TinySTL::fill(_First, _Last, _Val);
	}
	template<typename _FwdIt, typename T>
	void Pstar_uninitialized_fill_aux(_FwdIt _First, _FwdIt _Last, const T& _Val, __false_type) {
		for (; _First != _Last; ++_First)
			TinySTL::construct(_First, _Val);
	}

	template<typename _FwdIt, typename T>
	void uninitialized_fill(_FwdIt _First, _FwdIt _Last, const T& _Val) {
		typedef typename __type_traits<T>::is_POD_type		IS_POD_TYPE;
			Pstar_uninitialized_fill_aux(_First, _Last, _Val, IS_POD_TYPE());
	}


	/**********************************************************************
	名称：uninitialized_fill_n
	作用：对[_First，_First+_Count*sizeof(T)）范围内进行_Count个相同对象的构造，返回填充结束的位置
	***********************************************************************/
	template<typename _FwdIt, typename Size,typename T>
	_FwdIt Pstar_uninitialized_fill_n_aux(_FwdIt _First, Size _Count, const T& _Val, __true_type) {
		return TinySTL::fill_n(_First, _Count, _Val);
 	}

	template<typename _FwdIt , typename Size, typename T>
	_FwdIt Pstar_uninitialized_fill_n_aux(_FwdIt _First, Size _Count, const T& _Val, __false_type) {
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
	}

	template<typename _FwdIt, typename Size, typename T>
	_FwdIt uninitialized_fill_n(_FwdIt _First, Size _Count, const T& _Val) {
		typedef typename __type_traits<iterator_traits<_FwdIt>::value_type>::is_POD_type		IS_POD_TYPE;
		return Pstar_uninitialized_fill_n_aux(_First, _Count, _Val, IS_POD_TYPE());
	}

} //namespace TinySTL
#endif // !UNINITIALIZED_H
