/************************************************************
名称：allocator.h
作用：对alloc.h和construct.h进行封装，对外提供通用静态API。
说明：
	静态API，无需创建对象，使用 类名::即可进行调用
*************************************************************/
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include"alloc.h"
#include"construct.h"
#include"exceptdef.h"

#include<new>
namespace TinySTL {
	template<typename T>
	class allocator {
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
		//接口
		static T* allocate();
		static T* allocate(size_t _Count);
		static void deallocate(T* _Ptr);
		static void deallocate(T* _Ptr, size_t _Count);

		static void construct(T *_Ptr);
		static void construct(T *_Ptr, const T&_Val);
		static void destory(T *_Ptr);
		static void destory(T *_First, T *_Last);
	};

	template<typename T>
	T* allocator<T>::allocate() {
		return static_cast<T*>(TinySTL::alloc::allocate(sizeof(T)));
	}

	template<typename T>
	T* allocator<T>::allocate(size_t _Count) {
		if (_Count == 0)
			std::cerr << "申请内存需大于0";
		return static_cast<T*>(TinySTL::alloc::allocate(_Count * sizeof(T)));
	}

	template<typename T>
	void allocator<T>::deallocate(T *_Ptr) {
		TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T));
	}

	template<typename T>
	void allocator<T>::deallocate(T *_Ptr, size_t _Count) {
		if (_Count == 0) return;
		TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T)*_Count);
	}

	template<typename T>
	void allocator<T>::construct(T *_Ptr) {
		TinySTL::construct(_Ptr);
	}

	template<typename T>
	void allocator<T>::construct(T* _Ptr, const T&_Val) {
		TinySTL::construct(_Ptr, _Val);
	}

	template<typename T>
	void allocator<T>::destory(T *_Ptr) {
		TinySTL::destory(_Ptr);
	}
	template<typename T>
	void allocator<T>::destory(T *_First, T *_Last) {
		for (; _First != _Last; ++_First)
			TinySTL::destory(_First);
	}
} //namespace TinySTL
#endif // !ALLOCATOR_H

