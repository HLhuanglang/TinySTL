/*! @file
*********************************************************************
<PRE>
ģ����       : ͨ��
�ļ���       : uninitialized.h
����ļ�     : type_traits.h��iterator.h��
�ļ�ʵ�ֹ��� : �ṩͨ�õ��ڴ洦����
����         : �ɴ���Pstar
�汾         : 1.0
---------------------------------------------------------------------
���̰߳�ȫ�� : <��/��>[��˵��]
�쳣ʱ��ȫ�� : <��/��>[��˵��]
---------------------------------------------------------------------
��ע         : -
---------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���              �޸�����
2020/4/27    1.0     �ɴ���Pstar			   ����
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
������   : uninitialized_copy
����     : ����Χ(_First, _Last]��Ԫ�ظ��Ƶ�_Resultλ��
����     : 
		   [IN]		_First  : ������Χ����ʼ������
		   [IN]		_Last   : ������Χ�Ľ���������
		   [IN/OUT] _Result	: IN-Ŀ���������ʼ������,OUT-Ŀ������Ľ���λ��
����ֵ   : ����������� ������������������ _Result+(_Last-_Fistr)��������
�׳��쳣 : 
		   bad_alloc : ����newʧ��.�����ʺ�С��
-------------------------------------------------------------------------------
���Ӷ�   : -
��ע     : -
�����÷� : -
-------------------------------------------------------------------------------
����     : �ɴ���Pstar
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
			TinySTL::construct(&*_Tmp, *_First);	/*�����׳�bad_alloc�쳣*/
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
������   : uninitialized_fill
����     : �Է�Χ(_First, _Last]���ж�����䣬����ֵΪ_val
����     :
		   [IN]		_First  : ������Χ����ʼ������
		   [IN]		_Last   : ������Χ�Ľ���������
		   [IN]		_Val	: �������ֵ
����ֵ   : ��
�׳��쳣 : -
-------------------------------------------------------------------------------
���Ӷ�   : -
��ע     : -
�����÷� : -
-------------------------------------------------------------------------------
����     : �ɴ���Pstar
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
������   : uninitialized_fill_n
����     : ��_First��ʼ������λ�ý���_Count��������䣬����ֵΪ_val
����     :
		   [IN/OUT]	_First  : IN-Ŀ��λ����ʼ������,OUT-��������������
		   [IN]		_Count  : ���������
		   [IN]		_Val	: �������ֵ
����ֵ   : ����������λ�ô�����������_First+sizeof(T)*_Count��������
�׳��쳣 : -
-------------------------------------------------------------------------------
���Ӷ�   : -
��ע     : -
�����÷� : -
-------------------------------------------------------------------------------
����     : �ɴ���Pstar
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
