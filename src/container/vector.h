/************************************************************
���ƣ�vector.h
���ã�vector�����࣬����ʵ����vector��������
ʹ�ã�
vector<T>::test��vector��������
test.xxx() ͨ��vector����������еķ���
*************************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include"../fundation/allocator.h"
#include"../fundation/iterator.h"
#include"../fundation/utility.h"
#include"../algorithm/algorithm.h"
namespace TinySTL {
template<typename T>
class vector
{
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	
	using iterator = T*;
	using reverse_iterator = TinySTL::reverse_iterator<iterator>;
	using const_pointer = const T*;
	using const_iterator = const T*;
	using const_reference = const T&;
	using const_reverse_iterator = TinySTL::reverse_iterator<const iterator>;

	typedef TinySTL::reverse_iterator<const iterator>	const_reverse_iterator;
private:
	iterator Iter_first; //����������������λһ��vector
	iterator Iter_last;
	iterator Iter_end;
	using data_allocator = TinySTL::allocator<T>		;	//������allocator���ʵ�������ڵ���allocator���еķ���

public:
	/*vector API manual*/
	vector();
	explicit vector(const size_type _Nsize);
	vector(const size_type _Nsize, const value_type& _Val);
	template<typename InIt>
	vector(InIt _First, InIt _Last);
	vector(const vector& v);
	vector(vector&& v);
	vector& operator=(const vector& v);
	vector& operator=(vector&& v);
	~vector();

	iterator begin() { return Iter_first; }
	iterator end() { return Iter_last; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }



	data_allocator get_allocator() { return data_allocator; }
private:
	/*vector helper function��begin with Pstar_ */
	

};

template<class T>
vector<T>::vector()
{
	Iter_first = data_allocator::allocate(1);	//data_allocator().allocate(1)Ч��һ��
	Iter_last = Iter_first;
	Iter_end = Iter_first;
}

template<class T>
vector<T>::~vector()
{
	TinySTL::destory(Iter_first, Iter_end);
	data_allocator::deallocate(Iter_first, Iter_end-Iter_last);
}


}//namaspace TinySTL
#endif // !VECTOR_H
