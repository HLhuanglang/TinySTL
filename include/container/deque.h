/**************************************************************************************
���ƣ�deque.h
ע�⣺
***************************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include<deque>

#include"../fundation/iterator.h"
#include"../fundation/allocator.h"

namespace TinySTL {
/**************************************************************************************/
	//DEQUE PARAMETERS
#define _DEQUE_MAP_SIZE 8  /*minimum  map size, at least 1*/
template <class T>
	struct deque_buf_size
	{
		static constexpr size_t value = sizeof(T) < 256 ? 4096 / sizeof(T) : 16;
	};

	//CLASS TEMPLATE _Deque_iterator
template<class _Ty, class _Ref, class _Ptr>
	struct _Deque_iterator
		: public TinySTL::iterator<TinySTL::bidirectional_iterator_tag, _Ty> 
	{	//�̳��Ժ�������ͱ�Ӧ�ÿ��Բ���д�˰�
	typedef _Ty			value_type;
	typedef _Ptr		pointer;
	typedef _Ref		reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	typedef _Ty*	value_pointer;
	typedef _Ty**	map_node_pointer;
	static const size_type buffer_size = deque_buf_size<_Ty>::value;

	typedef _Deque_iterator<_Ty, _Ty&, _Ty*>				iterator;
	typedef _Deque_iterator<_Ty, const _Ty&, const _Ty*>	const_iterator;
	typedef _Deque_iterator<_Ty, _Ty&, _Ty*>				self;

	//�����ĸ���Ա����һ��������
	value_pointer		_Cur;	//ָ�������������ĵ�ǰԪ��
	value_pointer		_First;	//ָ��������������ͷ��
	value_pointer		_Last;	//ָ��������������β��
	map_node_pointer	_Node;	//ָ��map��ĳһ����㣬��ʾ���������ڵĽ��

	//���졢���ơ��ƶ�����
	_Deque_iterator() = default;

	_Deque_iterator(const iterator& _Right)
		: _Cur(_Right._Cur),
		_First(_Right._First),
		_Last(_Right._Last),
		_Node(_Right._Node)
	{	//�������캯��
	}
	
	_Deque_iterator(const const_iterator& _Right)
		: _Cur(_Right._Cur),
		_First(_Right._First),
		_Last(_Right._Last),
		_Node(_Right._Node)
	{	//�������캯��
	}

	_Deque_iterator(iterator && _Right)
		: _Cur(_Right._Cur),
		_First(_Right._First),
		_Last(_Right._Last),
		_Node(_Right._Node)
	{	//�ƶ�����
		_Right._Cur = nullptr;
		_Right._First = nullptr;
		_Right._Last = nullptr;
		_Right._Node = nullptr;
	}

	self& operator=(const iterator& _Right) 
	{	//���Ƶ�����
		if (this != &_Right) {
			_Cur = _Right._Cur;
			_First = _Right._First;
			_Last = _Right._Last;
			_Node = _Right._Node;
		}
		return *this;
	}

	//���������
	reference operator*() const { return*_Cur; }
	pointer operator->() const { return _Cur; }

	self& operator++()
	{	//++ǰ��
		++_Cur;
		if (_Cur == _Last) {
			_set_node(_Node+1);
			_Cur = _First;
		}
		return *this;
	}
	
	self operator++(int)
	{	//����++
		self _Tmp = *this;
		++*this;
		return _Tmp;
	}

	self& operator--()
	{
		--_Cur;
		if (_Cur == _First) {
			_set_node(_Node - 1);
			_Cur = _Last;
		}
		return *this;
	}

	self operator--(int) 
	{
		self _Tmp = *this;
		--*this;
		return _Tmp;
	}

	self& += (difference_type n)
	{	//��ǰ��n��Ԫ�أ����nΪ�������������
		difference_type _Off = n + (_Cur - _First);
		if (_Off >= 0
			&& _Off < difference_type(buffer_size()))
		{	//Ŀ��λ����Ȼ��ͬһ����������
			_Cur += n;
		}
		else
		{	//Ŀ��λ�ò���ͬһ��������
			difference_type _Node_offset = _Off > 0
				? _Off / difference_type(buffer_size())
				: -difference_type((-_Off - 1) / buffer_size()) - 1;
			_set_node(_Node + _Node_offset);	/*ȷ����ȷ�Ľ��λ��*/
			_Cur = _First + (_Off - _Node_offset * difference_type(buffer_size()));
		}
		return *this;
	}

	self operator+(difference_type n)const
	{	//�ø�ֵ��ʽ��op=��ȡ���䵥����ʽ��op��
		self _Tmp = *this;
		return _Tmp += n;
	}

	self& operator-=(difference_type n)
	{	//����operator+=�����
		return *this += -n;
	}

	self operator -(difference_type n)const
	{	
		self _Tmp = *this;
		return _Tmp -= n;
	}

	reference operator[](difference_type n) 
	{	//����operator*��operator+
		return *(*this + n);
	}	/*����Խ����*/

	//���رȽϲ�����
	bool operator==(const self& _Right) const { return _Cur == _Right._Cur; }
	bool operator!=(const self& _Right) const { return !(this == _Right); }
	bool operator<(const self& _Right) const 
	{	//���жϻ��������Ƿ���ͬ����ͬ��_Cur����ͬ��_Node
		return _Node == _Right._Node ? (_Cur < _Right._Cur) : (_Node < _Right._Node);
	}
	bool operator>(const self& _Right) const { return !(*this < _Right); }
	bool operator<=(const self& _Right)const { return !(*this > _Right); }
	bool operator>=(const self& _Right)const { return !(*this < _Right); }


	void _set_node(map_node_pointer _Next_node)
	{	//�������(Ҳ���Ǹ����µĻ�����)
		_Node = _Next_node;
		_First = *_Next_node;
		_Last = _First + buffer_size;
	}

	}; //end of _Deque_iterator class
/**************************************************************************************/
	//CLASS TEMPLATE deque
template<class T>
class deque {
	typedef TinySTL::allocator<T>	_Allocator_type;	
	typedef TinySTL::allocator<T*>	_Map_allocator;			//��������map��map��������ָ�룩
	typedef TinySTL::allocator<T>	_Buffer_allocator;		//��������buffer������Ҫ�Ŀռ�
	typedef TinySTL::allocator<T>	_Data_allocator;		//������buffer�ڴ������

	//��Ƕ�ͱ���(��_Alloccator_type��Ҫ���Ƿ����д��Ҳֻ����ֱ�Ӷ���typedef T value_type)
	typedef typename _Allocator_type::value_type			value_type;
	typedef typename _Allocator_type::pointer				pointer;
	typedef typename _Allocator_type::const_pointer			const_pointer;
	typedef typename _Allocator_type::reference				reference;
	typedef typename _Allocator_type::const_reference		const_reference;
	typedef typename _Allocator_type::size_type				size_type;
	typedef typename _Allocator_type::difference_type		difference_type;

	typedef pointer*		map_pointer;		//ָ��map��ָ��
	typedef const_pointer*	const_map_pointer;
	
	//����������
	typedef _Deque_iterator<T, T&, T*>							iterator;
	typedef _Deque_iterator<T, const T&, const T*>				const_iterator;
	typedef TinySTL::reverse_iterator<iterator>					reverse_iterator;
	typedef TinySTL::reverse_iterator<const_iterator>			const_reverse_iterator;

private:
	//��Ա��������
	iterator	_Begin;		//ָ���һ���ڵ�
	iterator	_End;		//ָ�����һ���ڵ�
	map_pointer _Map;		//ָ�����������map
	size_type	_Map_size;	//map���ж��ٸ�ָ�루����map���ݣ�

private:
	//������������
	map_pointer _create_map(size_type _Count);
	void _create_buffer(map_pointer _Start, map_pointer _End);
	void _map_buffer_init(size_type _nNode);
	void _fill_init(size_type _Count, const value_type& _Val);
	void _copy_init(iterator _First, iterator _Last);


public:
	//��Ա��������
	_Allocator_type get_allocator() { return _Allocator_type(); }
	
	/********************************************************************************/
	//�����졢���������ơ��ƶ�
	deque();
	deque(size_type _Count);
	deque(size_type _Count, value_type _Val);
	template<class Iter>
	deque(Iter _First, Iter _Last);
	deque(const deque& _Right);
	deque(deque&& _Right);
	deque& operator=(const deque& _Right);
	deque& operator=(deque&& _Right);
	deque& operator=(std::initializer_list<value_type> _List);
	~deque();
	
	/********************************************************************************/
	//���������


	/********************************************************************************/
	//Ԫ�ط������
	reference operator[](const size_type _Index);
	const_reference operator[](const size_type _Index);
	reference front();
	const_reference front();
	reference back();
	const_reference back();
	reference at(const size_type _Index);
	const_reference at(const size_type _Index);
	
	/********************************************************************************/
	//�������
	size_type size();
	size_type max_size();
	bool empty();
	void resize(size_type _New_size) { resize(_New_size, value_type()); }
	void resize(size_type _New_size, value_type _Val);
	void shrink_to_fit();
	
	/********************************************************************************/
	//�޸��������
	void clear();
	iterator erase(iterator _Where);
	iterator erase(iterator _First, iterator _Last);
	void swap(deque& _Right);

	void assign(size_type _Count, value_type _Val);
	template<class Iter>
	void assign(Iter _First, Iter _Last);
	
	void push_back(value_type _Val);
	void push_front(value_type _Val);
	void pop_back();
	void pop_back();

	void insert(iterator _Where, size_type _Count, const value_type _Val);
	void insert(iterator _Where, iterator _First, iterator _Last);
	iterator insert(iterator _Where, const value_type _Val);
};	//end of deque class

/********************************************************************************/
//helper functionʵ��
	/*
	�������ܣ�
	�������أ�
	*/


template<class T>
typename deque<T>::map_pointer 
deque<T>::_create_map(size_type _Count)
{	/*
	�������ܣ�����һ������_Count������map��ͬʱ��ʼ��(nullptr)���н��
	�������أ�����һ��ָ�룬ָ��map�׵�ַ
	*/
	map_pointer _Result = nullptr;
	_Result = _Map_allocator::allocate(_Count);
	for (size_type i = 0; i < _Count; ++i) {
		*(_Result + i) = nullptr;
	}
	return _Result;
}

template<class T>
void deque<T>::_create_buffer(map_pointer _Start, map_pointer _Finish)
{	/*
	�������ܣ�Ϊ[_Start, _Finish]�����ϵ�ÿһ��map��㣬����һ��buffer��������������map����ϡ�
	�������أ���
	*/
	map_pointer _Tmp = _Start;
	for (; _Tmp <= _Finish; _Tmp++) {
		*_Tmp = _Buffer_allocator::allocate(buffer_size);// *_Tmp����map����ֵ�����Ǹ�ָ�룩 
	}
}

template<class T>
void deque<T>::_map_buffer_init(size_type _Count)
{	/*
	�������ܣ���ʼ��map���Լ�����������������map�����
	����������_Count���ڼ�����Ҫ������ٸ�������
	*/
	const size_type _Node = _Count / buffer_size + 1;	/*����������*/

}


template<class T>
void deque<T>::_fill_init(size_type _Count, const value_type& _Val) {	
	/*
	�������ܣ���ʼ������ʱ������_Count��ֵΪ_Val��Ԫ��
	�������أ���
	*/

	//map��buffer��ʼ��
	//����uninitialized_fill���

}

	
/********************************************************************************/
//�����졢���������ơ��ƶ�ʵ��



} //namespace TinySTL
#endif // !DEQUE_H