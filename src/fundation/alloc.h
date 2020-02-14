/***************************************************************************************
���ƣ�alloc.h
���ã��ڴ����ͻ���
˵����
��free_list�Ϲ��ص��ǿ���ʹ�õ��ڴ�飬�����С�����ֳ�8��16��24�ȣ���union��ʽ���ڣ��ڲ�ָ���ŵ�����һ���ڴ��ĵ�ַ
�����е����롢�ͷŶ������ֽ���Ϊ��λ
***************************************************************************************/
#ifndef ALLOC_H
#define ALLOC_H

#include<new>
#include<iostream>
namespace TinySTL
{
#if !defined(_THROW_BAD_ALLOC)
#define _THROE_BAD_ALLOC  std::cerr<<"out of memory"<<std::endl; exit(1);

	//һ���ռ�������
	class __alloc {
	private:
		//���¶��Ǻ���ָ�룬������ĺ������������ڴ治������
		static void *oom_malloc(size_t);
		static void(*__oom_handler)();

	public:
		static void* allocate(size_t n)
		{
			void *result = malloc(n);
			if (result == 0)
				result = oom_malloc(n);
			return result;
		}

		static void deallocate(void *p, size_t /*n*/) {
			free(p);
		}

		static void(*set_malloc_hanlder(void(*f)()))(){
			void(*old)() = __oom_handler;
			__oom_handler = f;
			return old;
		}
	};

	void(*__alloc::__oom_handler)() = 0;
	void *__alloc::oom_malloc(size_t n) {
		void(*my_malloc_handler)();
		void *result;

		for (;;) {
			my_malloc_handler = __oom_handler;
			if (my_malloc_handler == 0) { _THROE_BAD_ALLOC; }
			(*my_malloc_handler)();	//���ú���ָ�룬�ͷ��ڴ�
			result = malloc(n);
			if (result) return result;
		}
	}
#endif

	/********************************************************************************************/
	class alloc
	{
	public:  //����ӿ�
		static void* allocate(size_t n);	//n����������ڴ��С
		static void  deallocate(void *p, size_t n); //n����128ֱ���ͷţ�С��128���յ�free_list��
		static void* reallocate(void *p, size_t old_size, size_t new_size); //���ͷţ��ٷ���

	private:
		union  obj_union
		{
			union obj_union* free_list_link;	//ָ����һ���ڴ��
			char client_data[1];						//�洢�����ڴ���׵�ַ
		};
	private:
		enum { __ALIGN = 8 };  //�ϵ��߽磨ת��Ϊ8�ı�����
		enum { __MAX_BYTES = 128 };  //С���ڴ�����ޣ�free_listά����������8*��15+1��=128��
		enum { __NFREELISTS = __MAX_BYTES / __ALIGN };  //free_listά�����ڴ��������

	private:
		static char* memory_pool_start;		//�ڴ����ʼλ�á� ֻ��chunk_alloc�б仯
		static char* memory_pool_end;		//�ڴ�ؽ���λ�á� ֻ��chunk_alloc�б仯
		static size_t heap_size;						//����heap�ռ丽��ֵ��С���������Խ�ֵ࣬Խ��
		static obj_union*  free_list[__NFREELISTS];  //ά���ڴ�����������

	private:
		static size_t m_round_up(size_t bytes);							//��������ڴ������8�ı�������30������Ϊ32��
		static size_t m_freelist_index(size_t bytes);						//����������ڴ��С������һ�����ʵ�free_list���
		static void* m_refill(size_t n);											//��free_list��ĳ��Ԫû���ڴ�ʱ�����ڴ������һ���ڴ�飬�����л���
		static char* m_chunk_alloc(size_t size, size_t& nobj);		//���ڴ�ز���ʱ����ϵͳ�ڴ�����ռ䣬���سɹ������ڴ�ĵ�ַ
	};

	//��̬������Ա��ʼ��
	char* alloc::memory_pool_start = nullptr; //char�պ���ռ��һ���ֽ�
	char* alloc::memory_pool_end = nullptr;
	size_t alloc::heap_size = 0;

	alloc::obj_union*  alloc::free_list[__NFREELISTS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };	//�ڴ���С8*(i+1)
	//free_list��ʼ��ȫ��0,���Ե�һ�δ���ʱ�ᵼ���ڴ�������Ϊ

	//�����СΪn�Ŀռ�
	void* alloc::allocate(size_t n)
	{
		if (n == 0) //����0�ֽ� 
			return 0;
		if (n > size_t(__MAX_BYTES)) 
		{
			void *p = __alloc::allocate(n);
			return p;
		}
		
		obj_union * volatile* my_free_list;
		obj_union  *result;
		my_free_list = free_list + m_freelist_index(n);
		result = *my_free_list;
		if (result == 0)
		{
			void* r = m_refill(m_round_up(n));
			return r;
		}
		*my_free_list = result->free_list_link;   //�����������ɾ������
		return result;
	}

	//�ͷ�pָ��Ĵ�СΪn�Ŀռ䣬���ظ�free_list
	void  alloc::deallocate(void *p, size_t n)
	{
		obj_union* volatile* my_free_list;
		obj_union* q = reinterpret_cast<obj_union*>(p);
		if (n > size_t(__MAX_BYTES))
		{
			__alloc::deallocate(p, n);
			return;
		}
		my_free_list = free_list + m_freelist_index(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}

	//���·���ռ�
	void* alloc::reallocate(void *p, size_t old_size, size_t new_size)
	{
		deallocate(p, old_size);
		p = allocate(new_size);
		return p;
	}

	//��bytes�ϵ�����Ӧ�����С
	inline size_t alloc::m_round_up(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) &  ~(__ALIGN - 1));
	}

	//���������С��ѡ���n��free lists
	inline size_t alloc::m_freelist_index(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) / __ALIGN - 1); //(30+7)/7-1=4-1=3
	}

	//���ڴ���з����ڴ��free_list�������ʵ���������nobj�Ĵ�С��nobjʵ�ʷ����˶��ٿ飩�����ط����ȥ���ڴ���׵�ַ
	char* alloc::m_chunk_alloc(size_t size, size_t& nobj)
	{
		size_t need_bytes = size * nobj;
		size_t left_bytes = memory_pool_end - memory_pool_start;
		char* result;
		//ʣ���ڴ��������20���ڴ�������
		if (need_bytes < left_bytes)
		{
			result = memory_pool_start;
			memory_pool_start += need_bytes;
			return result;
		}
		//�޷�����20����������������һ��
		else if (left_bytes > size)
		{
			nobj = left_bytes / size; //��������ܷ������
			need_bytes = size * nobj; //����һ��ʵ�������������
			result = memory_pool_start;
			memory_pool_start += need_bytes;
			return result;
		}

		//ʣ���ڴ��޷�����һ���ڴ�飬�Ȱ���ʣ�������free_list��ȥ��Ȼ������������
		else if (size > left_bytes)
		{
			//����ʣ���ڴ�
			if (left_bytes > 0) {
				obj_union* my_free_list = free_list[m_freelist_index(size)];
				((obj_union*)memory_pool_start)->free_list_link = my_free_list;
				my_free_list = (obj_union*)memory_pool_start;
			}
			//���������ڴ�
			size_t bytes_to_get = 2 * need_bytes;
			memory_pool_start = (char*)std::malloc(bytes_to_get);
			if (memory_pool_start == nullptr)
			{	//ϵͳ�ڴ涼������..��free_list�ϵ����е��ڴ漯������ȫ�������ڴ�أ��ٴ��ڴ�ط����ȥ
				obj_union* my_free_list,  *tmp;
				for (int i = size; i < __MAX_BYTES; i += __ALIGN)
				{
					my_free_list = free_list[m_freelist_index(i)];
					tmp = my_free_list;
					if (tmp) //��Ϊÿ���ڴ�鶼�Ǵ����һ���ڴ��ĵ�ַ�������һ��Ļ���Ϊ0��
					{
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
			return m_chunk_alloc(size, nobj);
		}
	}

	//����m_chunk_alloc���ڴ����ȡ���ڴ棬���ֳ�Ԥ���С������䵽free_list��Ӧλ��
	void* alloc::m_refill(size_t n)  //�����õ�ʱ�򣬴����n�Ѿ�����Ϊ8�ı�����
	{
		obj_union* volatile* my_free_list;
		obj_union* result, *cur_obj, *next_obj;
		size_t nobj = 20; //Ĭ�����ڴ������20��
		char* chunk = m_chunk_alloc(n, nobj);   //chunk �����void���ᵼ�� chunk+n�޷�ת��

		if (nobj == 1) //���ֻ���뵽1�飬��ֱ�ӷ��ظ�������
			return chunk;
		my_free_list = free_list + m_freelist_index(n);
		result = (obj_union*)chunk; //��һ��ֱ�ӷ��ظ�������

		//begin ��ʣ�µ�19���ڴ棬���վ����С���л���
		*my_free_list = next_obj = (obj_union*)(chunk + n);
		for (int i = 1; ; ++i)
		{
			cur_obj = next_obj;
			next_obj = (obj_union*)((char*)next_obj + n);
			if (nobj - 1 == i) //��i=19��ʱ��Ҳ�������һ���ڴ�
			{
				cur_obj->free_list_link = 0;
				return result;
				break;
			}
			else
			{
				cur_obj->free_list_link = next_obj;
			}
		}
		//end
		return result;
	}

}  //namespace TinySTL
#endif // !ALLOC_H
