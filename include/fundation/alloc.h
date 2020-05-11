/*! @file
*********************************************************************
<PRE>
ģ����       : �ڴ������
�ļ���       : alloc.h
����ļ�     : allocator.h
�ļ�ʵ�ֹ���	: ����������ԣ�ͨ���ڴ��ʵ�ָ�Ч���ڴ����
����         : �ɴ���Pastr
�汾         : 1.0
---------------------------------------------------------------------
���̰߳�ȫ�� : ����δ����
�쳣ʱ��ȫ�� : �ǣ�
---------------------------------------------------------------------
��ע         : ���ļ��ṩ���������ýӿ�����ײ���ڴ���亯������allocator����װ��
---------------------------------------------------------------------
�޸ļ�¼ :
�� ��			�汾     �޸���              �޸�����
2020��4��27��	1.0    �ɴ���Pstar			  ����
</PRE>
====================================================================
*	���ò�Σ�alloc -> __alloc
*	ʹ�÷�����������ͷ�ļ���#include"alloc.h"
�����ڴ�TinySTL::alloc::allocate()���ͷ��ڴ�TinySTL::alloc::deallocate()
********************************************************************/
#pragma once
#ifndef ALLOC_H
#define ALLOC_H

#include"exceptdef.h"

#include<new>
#include<iostream>

namespace TinySTL
{
#if !defined(_THROW_BAD_ALLOC)
#define _THROE_BAD_ALLOC  std::cerr<<"out of memory"<<std::endl; exit(1);

///////////////////////////////////////////////////////////////
//һ���ռ�������
class __alloc 
{
private:
	//���¶��Ǻ���ָ�룬������ĺ������������ڴ治������
	static void *oom_malloc(size_t);
	static void(*__oom_handler)();

public:
	static void* allocate(size_t _Size)
	{
		void *result = malloc(_Size);
		if (result == 0) {
			result = oom_malloc(_Size);
		}
		return result;
	}

	static void deallocate(void *_Ptr, size_t /*_Size*/)
	{
		free(_Ptr);
	}

	static void(*set_malloc_hanlder(void(*f)()))()
	{
		void(*old)() = __oom_handler;
		__oom_handler = f;
		return old;
	}
};//end of class __alloc

void(*__alloc::__oom_handler)() = 0;
void *__alloc::oom_malloc(size_t _Size) 
{
	void(*my_malloc_handler)();
	void *result;

	for (;;) {
		my_malloc_handler = __oom_handler;
		if (my_malloc_handler == 0) {
			_THROE_BAD_ALLOC;
		}
		(*my_malloc_handler)();	//���ú���ָ�룬�ͷ��ڴ�
		result = malloc(_Size);
		if (result) {
			return result;
		}
	}
}
#endif

////////////////////////////////////////////////////////////////////
//�����ռ�������
class alloc
{
public:
	static void* allocate(IN size_t _Size);	//_Size����������ڴ��С
	static void  deallocate(IN void *_Ptr, IN size_t _Size); //_Size����128ֱ���ͷţ�С��128���յ�free_list��
	static void* reallocate(IN void *_Ptr, IN size_t old_size, IN size_t new_size); //���ͷţ��ٷ���

private:
	union  obj_union
	{
		union obj_union* free_list_link;	//ָ����һ���ڴ��
		char client_data[1];				//�洢�����ڴ���׵�ַ
	};
private:
	enum { __ALIGN = 8 };  //�ϵ��߽磨ת��Ϊ8�ı�����
	enum { __MAX_BYTES = 128 };  //С���ڴ�����ޣ�free_listά����������8*��15+1��=128��
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };  //free_listά�����ڴ��������

private:
	static char* memory_pool_start;	//�ڴ����ʼλ�á� ֻ��chunk_alloc�б仯
	static char* memory_pool_end;	//�ڴ�ؽ���λ�á� ֻ��chunk_alloc�б仯
	static size_t heap_size;	//����heap�ռ丽��ֵ��С���������Խ�ֵ࣬Խ��
	static obj_union*  free_list[__NFREELISTS];	//ά���ڴ�����������

private:
	static size_t Pstar_round_up(IN size_t bytes);	//��������ڴ������8�ı�������30������Ϊ32��
	static size_t Pstar_freelist_index(IN size_t bytes);	//����������ڴ��С������һ�����ʵ�free_list���
	static void* Pstar_refill(IN size_t _Size);	//��free_list��ĳ��Ԫû���ڴ�ʱ�����ڴ������һ���ڴ�飬�����л���
	static char* Pstar_chunk_alloc(IN size_t _Size, IN size_t& _Count);	//���ڴ�ز���ʱ����ϵͳ�ڴ�����ռ䣬���سɹ������ڴ�ĵ�ַ
};


/*static*/char* alloc::memory_pool_start = nullptr;
/*static*/char* alloc::memory_pool_end = nullptr;
/*static*/size_t alloc::heap_size = 0;
/*static*/alloc::obj_union*  alloc::free_list[__NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	//�ڴ���С8*(i+1)



//=============================================================================
//======================================================================�����ӿ�
//�����СΪ_Size�Ŀռ�
void* alloc::allocate(IN size_t _Size)
{
	if (_Size == 0) {
		return 0;
	}
	if (_Size > size_t(__MAX_BYTES)) {
		void *_Ptr = __alloc::allocate(_Size);
		return _Ptr;
	}
		
	obj_union * volatile* my_free_list;
	obj_union  *result;
	my_free_list = free_list + Pstar_freelist_index(_Size);
	result = *my_free_list;
	
	if (result == 0){
		void* r = Pstar_refill(Pstar_round_up(_Size));
		return r;
	}
	*my_free_list = result->free_list_link;   //�����������ɾ������
	return result;
}

//�ͷ�_Ptrָ��Ĵ�СΪ_Size�Ŀռ䣬���ظ�free_list
void  alloc::deallocate(IN void *_Ptr, IN size_t _Size)
{
	obj_union* volatile* my_free_list;
	obj_union* q = reinterpret_cast<obj_union*>(_Ptr);

	if (_Size > size_t(__MAX_BYTES)){
		__alloc::deallocate(_Ptr, _Size);
		return;
	}
	
	my_free_list = free_list + Pstar_freelist_index(_Size);
	q->free_list_link = *my_free_list;
	*my_free_list = q;
}

//���·���ռ�
void* alloc::reallocate(IN void *_Ptr, IN size_t old_size, IN size_t new_size)
{
	deallocate(_Ptr, old_size);
	_Ptr = allocate(new_size);
	return _Ptr;
}
//=====================================================================�����ӿ�
//============================================================================



//��bytes�ϵ�����Ӧ�����С
inline size_t alloc::Pstar_round_up(IN size_t bytes)
{
	return (((bytes)+__ALIGN - 1) &  ~(__ALIGN - 1));
}

//���������С��ѡ���_Size��free lists
inline size_t alloc::Pstar_freelist_index(IN size_t bytes)
{
	return (((bytes)+__ALIGN - 1) / __ALIGN - 1); //(30+7)/7-1=4-1=3
}

//���ڴ���з����ڴ��free_list�������ʵ���������_Count�Ĵ�С��_Countʵ�ʷ����˶��ٿ飩�����ط����ȥ���ڴ���׵�ַ
char* alloc::Pstar_chunk_alloc(IN size_t _Size, IN size_t& _Count)
{
	size_t need_bytes = _Size * _Count;
	size_t left_bytes = memory_pool_end - memory_pool_start;
	char* result;
	if (need_bytes < left_bytes){	//ʣ���ڴ��������20���ڴ�������
		result = memory_pool_start;
		memory_pool_start += need_bytes;
		return result;
	}else if (left_bytes > _Size){	//�޷�����20����������������һ��
		_Count = left_bytes / _Size; //��������ܷ������
		need_bytes = _Size * _Count; //����һ��ʵ�������������
		result = memory_pool_start;
		memory_pool_start += need_bytes;
		return result;
	}else if (_Size > left_bytes){//ʣ���ڴ��޷�����һ���ڴ�飬�Ȱ�ʣ�������free_list��ȥ��Ȼ������������
		if (left_bytes > 0) {//����ʣ���ڴ�
			obj_union* my_free_list = free_list[Pstar_freelist_index(_Size)];
			((obj_union*)memory_pool_start)->free_list_link = my_free_list;
			my_free_list = (obj_union*)memory_pool_start;
		}
		//���������ڴ�
		size_t bytes_to_get = 2 * need_bytes;
		memory_pool_start = (char*)std::malloc(bytes_to_get);
		if (memory_pool_start == nullptr){	//ϵͳ�ڴ涼������..��free_list�ϵ����е��ڴ漯������ȫ�������ڴ�أ��ٴ��ڴ�ط����ȥ
			obj_union* my_free_list,  *tmp;
			for (int i = _Size; i < __MAX_BYTES; i += __ALIGN){
				my_free_list = free_list[Pstar_freelist_index(i)];
				tmp = my_free_list;
				if (tmp){	//��Ϊÿ���ڴ�鶼�Ǵ����һ���ڴ��ĵ�ַ�������һ��Ļ���Ϊ0��
					my_free_list = tmp->free_list_link;
					memory_pool_start = (char*)tmp; //�ڴ��Ϊ���ˣ����Կ������¶�λstart��end��λ��
					memory_pool_end = memory_pool_start + i;
				}
			}
			std::printf("out of memory");
			memory_pool_end = nullptr; //��ӦstartΪnullptr
			throw std::bad_alloc();
		}
		memory_pool_end = bytes_to_get + memory_pool_start;
		return Pstar_chunk_alloc(_Size, _Count);
	}
}

//����Pstar_chunk_alloc���ڴ����ȡ���ڴ棬���ֳ�Ԥ���С������䵽free_list��Ӧλ��
void* alloc::Pstar_refill(IN size_t _Size)  //�����õ�ʱ�򣬴����_Size�Ѿ�����Ϊ8�ı�����
{
	obj_union* volatile* my_free_list;
	obj_union* result, * cur_obj, * next_obj;
	size_t _Count = 20; //Ĭ�����ڴ������20��
	char* chunk = Pstar_chunk_alloc(_Size, _Count);   //chunk �����void���ᵼ�� chunk+_Size�޷�ת��

	if (_Count == 1){ //���ֻ���뵽1�飬��ֱ�ӷ��ظ�������
		return chunk; }

	my_free_list = free_list + Pstar_freelist_index(_Size);
	result = (obj_union*)chunk; //��һ��ֱ�ӷ��ظ�������

	//begin ��ʣ�µ�19���ڴ棬���վ����С���л���
	*my_free_list = next_obj = (obj_union*)(chunk + _Size);
	for (int i = 1; ; ++i){
		cur_obj = next_obj;
		next_obj = (obj_union*)((char*)next_obj + _Size);
		if (_Count - 1 == i){//��i=19��ʱ��Ҳ�������һ���ڴ�
			cur_obj->free_list_link = 0;
			return result;
			break;
		}else{
			cur_obj->free_list_link = next_obj;
		}
	}
	//end
	return result;
}
}  //namespace TinySTL
#endif // !ALLOC_H
