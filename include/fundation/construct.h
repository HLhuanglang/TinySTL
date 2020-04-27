/*! @file
*********************************************************************
<PRE>
ģ����       : �ڴ������
�ļ���       : construct.h
����ļ�     : allocator.h
�ļ�ʵ�ֹ��� : �ṩ���������������ܺ���
����         : �ɴ���Pstar
�汾         : 1.0
---------------------------------------------------------------------
���̰߳�ȫ�� : ����δ����
�쳣ʱ��ȫ�� : ��
---------------------------------------------------------------------
��ע         : 
---------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���            �޸�����
2020/04/27   1.0   �ɴ���Pstar			 ����
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
	Pstar_destory(_First, _Last, IS_POD_TYPE()/*���ſ���ʡ��*/);
}

template<typename _InIt>
inline void Pstar_destory(IN _InIt _First, IN _InIt _Last, DUMMY __true_type _True) 
{
	//�������ͣ������������ν�����Բ�������
}

template<typename _InIt>
inline void Pstar_destory(IN _InIt _First, IN _InIt _Last, DUMMY __false_type _False) 
{	//�����������ͣ������û��Զ������ͣ���Ҫ�����ͷ���Դ
	while (_First != _Last)
	{
		destory(&*_First); //*_Firstȡ�����ݣ�����&ȡ�õ�ַ
		++_First;
	}
}

} //namespace TinySTL
#endif // !CONSTRUCT_H

