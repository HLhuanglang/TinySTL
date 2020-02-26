/************************************************************
���ƣ�allocator.h
���ã���alloc.h��construct.h���з�װ�������ṩͨ�þ�̬API��
˵����
	��̬API�����贴������ʹ�� ����::���ɽ��е���
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
		//��дҲ�ǿ��Եģ�ֻ�ǹ���ͳһ�������ͱ𣬷������Ϳɶ���
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using difference_type = ptrdiff_t;
		using size_type = size_t;
		using const_reference = const T&;
		using const_pointer = const T*;


	public:
		//�ӿ�
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
			std::cerr << "�����ڴ������0";
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

