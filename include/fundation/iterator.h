/*! @file
*********************************************************************
<PRE>
ģ����       : ������
�ļ���       : iterator.h
����ļ�     : ��
�ļ�ʵ�ֹ��� : �ṩ�������ͷ����������
����         : �ɴ���Pstar
�汾         : 1.0
---------------------------------------------------------------------
���̰߳�ȫ�� : <��/��>[��˵��]
�쳣ʱ��ȫ�� : <��/��>[��˵��]
---------------------------------------------------------------------
��ע         : <����˵��>
---------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���              �޸�����
2020/4/27    1.0     �ɴ���Pstar			  ����
</PRE>
********************************************************************/


#ifndef ITERATOR_H
#define ITERATOR_H

#include"exceptdef.h"
#include<cstddef> //Ϊ��ʹ��ptrdiff_t(һ���������ص��������ͣ�ptrdiff_t���ͱ���ͨ��������������ָ����������Ľ��)

namespace TinySTL {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//input_iterator
//��������ָ���󣬲��������ı䣬read only
template<class T, class Distance>
struct input_iterator {
	typedef input_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T*	pointer;
	typedef T&	reference;
};

//output_iterator
//write only
template <class T, class Distance>
struct output_iterator {
	typedef output_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};

//forward_iterator
//����д���͡��㷨�ڴ��ֵ��������γɵ������Ͻ��ж�д����
template <class T, class Distance>
struct forward_iterator {
	typedef forward_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};

//bidirectional_iterator
//��˫���ƶ�����������ʵ����������ڵ�Ԫ��,������Ծ����
template <class T, class Distance>
struct bidirectional_iterator {
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};

//random_access_iterator
//��������ָ��������p+n,p-n��
template <class T, class Distance>
struct random_access_iterator {
	typedef random_access_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};



//���̳У��� class ListIterator�� public iterator<bidirectional_iterator_tag, T>
template<class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T * ,
	class Reference = T & >
struct iterator 
{
	typedef Category		iterator_catagory;
	typedef T				value_type;
	typedef Distance		difference_type;
	typedef Pointer			pointer;
	typedef Reference		reference;
};

//��ȡ����������
//���ģ��Ϊ���������������Զ�����һ�ױ�׼�����ͱ��������㷨�ȿ����õ�������Ҳ������һ���ָ��
template<typename Iterator>
struct iterator_traits 
{
	typedef typename Iterator::iterator_category		iterator_category;
	typedef typename Iterator::value_type				value_type;
	typedef typename Iterator::difference_type			difference_type;
	typedef typename Iterator::pointer					pointer;
	typedef typename Iterator::reference				reference;
};

//���pointer ��pointer-to-const�����ػ�
/*
	������ʵ�������Ҫ���ȫ���������������õ�ָ���ϣ���˶���ָ�룬iterator_category
	���ǵ�ͬ��random_access_iterator_tag
*/
template<typename T>
struct iterator_traits<T*> 
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef ptrdiff_t	difference_type;
	typedef T*	pointer;
	typedef T&	reference;
};

template<typename T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef ptrdiff_t	difference_type;
	typedef const T*	pointer;
	typedef const T&	reference;
};

//������������category
template<typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator&) 
{
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}

//��������distance type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type
	distance_type(const Iterator&) 
{
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

//��������value type
template<typename Iterator>
inline typename iterator_traits<Iterator>::value_type*
	value_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

/**************************************************************************
�� �� ����distance
�������ã���������������֮��ľ���
�� �� ֵ��
**************************************************************************/
template<class _InIt>
typename iterator_traits<_InIt>::difference_type
	distance(IN _InIt _First, IN _InIt _Last) 
{
	return Pstar_distance(_First, _Last, iterator_category(_First));
}

//distance��input_iterator_tag�汾
template<class _InIt>
typename iterator_traits<_InIt>::difference_type
	Pstar_distance(IN _InIt _First, IN _InIt _Last, DUMMY input_iterator_tag) 
{
	typename iterator_traits<_InIt>::difference_type _Dis = 0;
	while (_First != _Last) {
		++_First;
		++_Dis;
	}
	return _Dis;
}

//distance��random_access_iterator_tag�汾
template <class _RanIt>
typename iterator_traits<_RanIt>::difference_type
	Pstar_distance(IN _RanIt _First, IN _RanIt _Last, DUMMY random_access_iterator_tag)
{	/*�������iterator���಻��random���ͣ�������farward�������������input�汾����Ϊfarward�̳���input*/
	return (_Last - _First);
}

/**************************************************************************
�� �� ����advance
�������ã�ʹ������iterǰ��n������
�� �� ֵ����
ע �� �㣺n������������ǰ�����Ǻ��ˣ�����ǰ������������
**************************************************************************/

template<class _InIt, class _Distance>
inline void advance(IN _InIt& i, IN _Distance n)
{
	Pstar_advance(i, n, iterator_category(i));
}

template<class _InIt, class _Distance>
inline void Pstar_advance(IN _InIt& i, IN _Distance n, DUMMY input_iterator_tag)
{	/*advance�㷨��forward_iter��input_iteratorЧ����һ���ģ����ڼ̳й�ϵ����ֻʵ��input_iterator*/
	while (n--) ++i;
}

template<class _InIt, class _Distance>
inline void Pstar_advance(IN _InIt& i, IN _Distance n, DUMMY bidirectional_iterator_tag)
{
	if (n >= 0)
		while (n--)++i;
	else
		while (n++)--i;
}
	
template<class _InIt, class _Distance>
inline void Pstar_advance(IN _InIt& i, IN _Distance n, DUMMY random_access_iterator_tag)
{
	i += n;
}

//**********************************************************************************
//reverse_iterator
template<class Iterator>
class reverse_iterator 
{
public:
	using iterator_category = typename TinySTL::iterator_traits<Iterator>::iterator_category;
	using value_type = typename TinySTL::iterator_traits<Iterator>::value_type;
	using differece_type = typename TinySTL::iterator_traits<Iterator>::difference_type;
	using pointer = typename TinySTL::iterator_traits<Iterator>::pointer;
	using reference = typename TinySTL::iterator_traits<Iterator>::reference;

	using iterator_type = Iterator;
	using self = reverse_iterator<Iterator>;
private:
	Iterator Cur;
public:
	//���캯��
	reverse_iterator() = default;
	explicit reverse_iterator(iterator_type iter) : Cur(iter) {}
	reverse_iterator(const self& _Right) : Cur(_Right.Cur) {}

public:
	//��ȡ��Ӧ�����������
	iterator_type base() const
	{
		return Cur;
	}

	reference operator*() const 
	{
		Iterator _Temp = Cur;
		return *--_Temp;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	self& operator++()
	{
		--Cur;
		return *this;
	}

	self& operator++(int)
	{
		self _Temp = *this;
		--Cur;
		return _Temp;
	}

	self& operator--()
	{
		++Cur;
		return *this;
	}

	self& operator--(int)
	{
		self _Temp = *this;
		++Cur;
		return _Temp;
	}

	self& operator+(differece_type n) const
	{
		return self(Cur - n);
	}

	self& operator+=(differece_type n) const
	{
		Cur -= n;
		return *this;
	}

	self& operator-(differece_type n)const
	{
		return self(Cur + n);
	}
		
	self& operator-=(differece_type n) const
	{
		Cur += n;
		return *this;
	}

	reference operator[](differece_type n) const
	{
		return *(*this + n);
	}
};//end of class reverse_iterator


//����
template<class Iter>
typename TinySTL::reverse_iterator<Iter>::difference_type
	operator-(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return _Right.base() - _Left.base();
}

template<class Iter>
bool operator==(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return _Right.base() == _Left.base();
}

template<class Iter>
bool operator!=(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return !(_Left == _Right);
}

template<class Iter>
bool operator<(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return _Right.base() < _Left.base();
}

template<class Iter>
bool operator>(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return _Right < _Left;
}

template<class Iter>
bool operator<=(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return !(_Right < _Left);
}

template<class Iter>
bool operator>=(const reverse_iterator<Iter>& _Left, const reverse_iterator<Iter>& _Right)
{
	return !(_Left < _Right);
}

} //namespace TinySTL
#endif // !ITERATOR_H