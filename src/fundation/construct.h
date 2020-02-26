/**************************************************************
���ƣ�construct.h
���ã��������Ĺ��������
˵�����ṩ4��ͨ��API
	construct(ָ��)		construct(ָ�룬ֵ)
	destory(ָ��)		destory(ָ�룬ֵ��
**************************************************************/

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include"type_traits.h"
#include<new>  //for placement new

namespace TinySTL {
	
	template<typename T1>
	inline void construct(T1* _Ptr) {
		new(_Ptr) T1();
	}
	
	template<typename T1, typename T2>
	inline void construct(T1 *_Ptr, const T2& _Val) {
		new(_Ptr) T1(_Val);
	}
	
	template<typename T>
	inline void destory(T *_Ptr) {
		_Ptr->~T();
	}

	template<typename _InIt>
	inline void Pstar_destory(_InIt _First, _InIt _Last, __true_type _True) {
		//�������ͣ������������ν�����Բ�������
	}

	template<typename _InIt>
	inline void Pstar_destory(_InIt _First, _InIt _Last, __false_type _False) {
		//�����������ͣ������û��Զ������ͣ���Ҫ�����ͷ���Դ
		while (_First != _Last)
		{
			destory(&*_First); //*_Firstȡ�����ݣ�����&ȡ�õ�ַ
			++_First;
		}
	}

	template<typename _InIt>
	inline void destory(_InIt _First, _InIt _Last) {
		typedef typename __type_traits<_InIt>::is_POD_type		IS_POD_TYPE;
		Pstar_destory(_First, _Last, IS_POD_TYPE()/*���ſ���ʡ��*/);
	}

} //namespace TinySTL
#endif // !CONSTRUCT_H

