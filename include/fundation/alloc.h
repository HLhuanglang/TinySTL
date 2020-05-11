/*! @file
*********************************************************************
<PRE>
模块名       : 内存分配器
文件名       : alloc.h
相关文件     : allocator.h
文件实现功能	: 两级分配策略，通过内存池实现高效的内存分配
作者         : 派大星Pastr
版本         : 1.0
---------------------------------------------------------------------
多线程安全性 : 否，暂未考虑
异常时安全性 : 是，
---------------------------------------------------------------------
备注         : 该文件提供的三个公用接口是最底层的内存分配函数，被allocator所封装。
---------------------------------------------------------------------
修改记录 :
日 期			版本     修改人              修改内容
2020年4月27日	1.0    派大星Pstar			  创建
</PRE>
====================================================================
*	调用层次：alloc -> __alloc
*	使用方法：包含该头文件，#include"alloc.h"
分配内存TinySTL::alloc::allocate()、释放内存TinySTL::alloc::deallocate()
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
//一级空间配置器
class __alloc 
{
private:
	//以下都是函数指针，所代表的函数用来处理内存不足的情况
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
		(*my_malloc_handler)();	//调用函数指针，释放内存
		result = malloc(_Size);
		if (result) {
			return result;
		}
	}
}
#endif

////////////////////////////////////////////////////////////////////
//二级空间配置器
class alloc
{
public:
	static void* allocate(IN size_t _Size);	//_Size代表申请的内存大小
	static void  deallocate(IN void *_Ptr, IN size_t _Size); //_Size大于128直接释放，小于128回收到free_list中
	static void* reallocate(IN void *_Ptr, IN size_t old_size, IN size_t new_size); //先释放，再分配

private:
	union  obj_union
	{
		union obj_union* free_list_link;	//指向下一个内存块
		char client_data[1];				//存储本块内存的首地址
	};
private:
	enum { __ALIGN = 8 };  //上调边界（转换为8的倍数）
	enum { __MAX_BYTES = 128 };  //小型内存块上限（free_list维护的最大块是8*（15+1）=128）
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };  //free_list维护的内存块链个数

private:
	static char* memory_pool_start;	//内存池起始位置。 只在chunk_alloc中变化
	static char* memory_pool_end;	//内存池结束位置。 只在chunk_alloc中变化
	static size_t heap_size;	//申请heap空间附加值大小（申请次数越多，值越大）
	static obj_union*  free_list[__NFREELISTS];	//维护内存块的自由链表

private:
	static size_t Pstar_round_up(IN size_t bytes);	//将申请的内存调整至8的倍数（如30，调整为32）
	static size_t Pstar_freelist_index(IN size_t bytes);	//根据申请的内存大小，返回一个合适的free_list序号
	static void* Pstar_refill(IN size_t _Size);	//当free_list中某单元没有内存时，向内存池申请一批内存块，并进行划分
	static char* Pstar_chunk_alloc(IN size_t _Size, IN size_t& _Count);	//当内存池不够时，向系统内存申请空间，返回成功分配内存的地址
};


/*static*/char* alloc::memory_pool_start = nullptr;
/*static*/char* alloc::memory_pool_end = nullptr;
/*static*/size_t alloc::heap_size = 0;
/*static*/alloc::obj_union*  alloc::free_list[__NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	//内存块大小8*(i+1)



//=============================================================================
//======================================================================公共接口
//分配大小为_Size的空间
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
	*my_free_list = result->free_list_link;   //类似于链表的删除操作
	return result;
}

//释放_Ptr指向的大小为_Size的空间，返回给free_list
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

//重新分配空间
void* alloc::reallocate(IN void *_Ptr, IN size_t old_size, IN size_t new_size)
{
	deallocate(_Ptr, old_size);
	_Ptr = allocate(new_size);
	return _Ptr;
}
//=====================================================================公共接口
//============================================================================



//将bytes上调至对应区间大小
inline size_t alloc::Pstar_round_up(IN size_t bytes)
{
	return (((bytes)+__ALIGN - 1) &  ~(__ALIGN - 1));
}

//根据区块大小，选择第_Size个free lists
inline size_t alloc::Pstar_freelist_index(IN size_t bytes)
{
	return (((bytes)+__ALIGN - 1) / __ALIGN - 1); //(30+7)/7-1=4-1=3
}

//从内存池中分配内存给free_list，会根据实际情况调整_Count的大小（_Count实际分配了多少块），返回分配出去的内存的首地址
char* alloc::Pstar_chunk_alloc(IN size_t _Size, IN size_t& _Count)
{
	size_t need_bytes = _Size * _Count;
	size_t left_bytes = memory_pool_end - memory_pool_start;
	char* result;
	if (need_bytes < left_bytes){	//剩余内存可以满足20个内存块的请求
		result = memory_pool_start;
		memory_pool_start += need_bytes;
		return result;
	}else if (left_bytes > _Size){	//无法满足20个，但至少能满足一个
		_Count = left_bytes / _Size; //计算具体能分配多少
		need_bytes = _Size * _Count; //更新一下实际能满足的需求
		result = memory_pool_start;
		memory_pool_start += need_bytes;
		return result;
	}else if (_Size > left_bytes){//剩余内存无法满足一个内存块，先把剩余的塞进free_list中去，然后再重新申请
		if (left_bytes > 0) {//处理剩余内存
			obj_union* my_free_list = free_list[Pstar_freelist_index(_Size)];
			((obj_union*)memory_pool_start)->free_list_link = my_free_list;
			my_free_list = (obj_union*)memory_pool_start;
		}
		//重新申请内存
		size_t bytes_to_get = 2 * need_bytes;
		memory_pool_start = (char*)std::malloc(bytes_to_get);
		if (memory_pool_start == nullptr){	//系统内存都不够了..把free_list上的现有的内存集合起来全部还给内存池，再从内存池分配出去
			obj_union* my_free_list,  *tmp;
			for (int i = _Size; i < __MAX_BYTES; i += __ALIGN){
				my_free_list = free_list[Pstar_freelist_index(i)];
				tmp = my_free_list;
				if (tmp){	//因为每个内存块都是存的下一个内存块的地址，到最后一块的话就为0了
					my_free_list = tmp->free_list_link;
					memory_pool_start = (char*)tmp; //内存池为空了，所以可以重新定位start、end的位置
					memory_pool_end = memory_pool_start + i;
				}
			}
			std::printf("out of memory");
			memory_pool_end = nullptr; //对应start为nullptr
			throw std::bad_alloc();
		}
		memory_pool_end = bytes_to_get + memory_pool_start;
		return Pstar_chunk_alloc(_Size, _Count);
	}
}

//调用Pstar_chunk_alloc从内存池中取得内存，划分成预设大小，并填充到free_list相应位置
void* alloc::Pstar_refill(IN size_t _Size)  //被调用的时候，传入的_Size已经调整为8的倍数了
{
	obj_union* volatile* my_free_list;
	obj_union* result, * cur_obj, * next_obj;
	size_t _Count = 20; //默认向内存池申请20块
	char* chunk = Pstar_chunk_alloc(_Size, _Count);   //chunk 如果是void，会导致 chunk+_Size无法转型

	if (_Count == 1){ //如果只申请到1块，就直接返回给调用者
		return chunk; }

	my_free_list = free_list + Pstar_freelist_index(_Size);
	result = (obj_union*)chunk; //第一块直接返回给调用者

	//begin 对剩下的19块内存，按照具体大小进行划分
	*my_free_list = next_obj = (obj_union*)(chunk + _Size);
	for (int i = 1; ; ++i){
		cur_obj = next_obj;
		next_obj = (obj_union*)((char*)next_obj + _Size);
		if (_Count - 1 == i){//当i=19的时候，也就是最后一块内存
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
