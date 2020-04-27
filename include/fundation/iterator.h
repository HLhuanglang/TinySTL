/*! @file
*********************************************************************
<PRE>
模块名       : 迭代器
文件名       : iterator.h
相关文件     : 无
文件实现功能 : 提供迭代器和反向迭代器类
作者         : 派大星Pstar
版本         : 1.0
---------------------------------------------------------------------
多线程安全性 : <是/否>[，说明]
异常时安全性 : <是/否>[，说明]
---------------------------------------------------------------------
备注         : <其它说明>
---------------------------------------------------------------------
修改记录 :
日 期        版本     修改人              修改内容
2020/4/27    1.0     派大星Pstar			  创建
</PRE>
********************************************************************/


#ifndef ITERATOR_H
#define ITERATOR_H

#include"exceptdef.h"
#include<cstddef> //为了使用ptrdiff_t(一个与机器相关的数据类型，ptrdiff_t类型变量通常用来保存两个指针减法操作的结果)

namespace TinySTL {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//input_iterator
//迭代器所指对象，不允许外界改变，read only
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
//允许“写入型”算法在此种迭代器所形成的区间上进行读写操作
template <class T, class Distance>
struct forward_iterator {
	typedef forward_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};

//bidirectional_iterator
//可双向移动，能逆向访问迭代器区间内的元素,不可跳跃访问
template <class T, class Distance>
struct bidirectional_iterator {
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};

//random_access_iterator
//涵盖所有指针能力，p+n,p-n等
template <class T, class Distance>
struct random_access_iterator {
	typedef random_access_iterator_tag	iterator_category;
	typedef T	value_type;
	typedef Distance	difference_type;
	typedef T* pointer;
	typedef T& reference;
};



//被继承，如 class ListIterator： public iterator<bidirectional_iterator_tag, T>
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

//萃取迭代器特性
//这个模板为迭代器的类型特性定义了一套标准的类型别名，让算法既可以用迭代器，也可以用一般的指针
template<typename Iterator>
struct iterator_traits 
{
	typedef typename Iterator::iterator_category		iterator_category;
	typedef typename Iterator::value_type				value_type;
	typedef typename Iterator::difference_type			difference_type;
	typedef typename Iterator::pointer					pointer;
	typedef typename Iterator::reference				reference;
};

//针对pointer 和pointer-to-const进行特化
/*
	随机访问迭代器所要求的全部操作都可以运用到指针上，因此对于指针，iterator_category
	总是等同于random_access_iterator_tag
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

//迭代器的类型category
template<typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator&) 
{
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}

//迭代器的distance type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type
	distance_type(const Iterator&) 
{
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

//迭代器的value type
template<typename Iterator>
inline typename iterator_traits<Iterator>::value_type*
	value_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

/**************************************************************************
函 数 名：distance
函数作用：计算两个迭代器之间的距离
返 回 值：
**************************************************************************/
template<class _InIt>
typename iterator_traits<_InIt>::difference_type
	distance(IN _InIt _First, IN _InIt _Last) 
{
	return Pstar_distance(_First, _Last, iterator_category(_First));
}

//distance的input_iterator_tag版本
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

//distance的random_access_iterator_tag版本
template <class _RanIt>
typename iterator_traits<_RanIt>::difference_type
	Pstar_distance(IN _RanIt _First, IN _RanIt _Last, DUMMY random_access_iterator_tag)
{	/*如果不是iterator种类不是random类型，假设是farward，则会调用上面的input版本，因为farward继承自input*/
	return (_Last - _First);
}

/**************************************************************************
函 数 名：advance
函数作用：使迭代器iter前进n个距离
返 回 值：无
注 意 点：n的正负决定是前进还是后退，正：前进，负：后退
**************************************************************************/

template<class _InIt, class _Distance>
inline void advance(IN _InIt& i, IN _Distance n)
{
	Pstar_advance(i, n, iterator_category(i));
}

template<class _InIt, class _Distance>
inline void Pstar_advance(IN _InIt& i, IN _Distance n, DUMMY input_iterator_tag)
{	/*advance算法对forward_iter和input_iterator效果是一样的，由于继承关系，可只实现input_iterator*/
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
	//构造函数
	reverse_iterator() = default;
	explicit reverse_iterator(iterator_type iter) : Cur(iter) {}
	reverse_iterator(const self& _Right) : Cur(_Right.Cur) {}

public:
	//获取对应的正向迭代器
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


//重载
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