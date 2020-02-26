/**************************************************************
名称：construct.h
作用：负责对象的构造和析构
说明：提供4个通用API
	construct(指针)		construct(指针，值)
	destory(指针)		destory(指针，值）
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
		//内置类型，析构与否都无所谓，所以不做处理
	}

	template<typename _InIt>
	inline void Pstar_destory(_InIt _First, _InIt _Last, __false_type _False) {
		//不是内置类型，属于用户自定义类型，需要析构释放资源
		while (_First != _Last)
		{
			destory(&*_First); //*_First取得内容，再用&取得地址
			++_First;
		}
	}

	template<typename _InIt>
	inline void destory(_InIt _First, _InIt _Last) {
		typedef typename __type_traits<_InIt>::is_POD_type		IS_POD_TYPE;
		Pstar_destory(_First, _Last, IS_POD_TYPE()/*括号可以省略*/);
	}

} //namespace TinySTL
#endif // !CONSTRUCT_H

