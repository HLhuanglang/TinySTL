/************************************************************
名称：iterator.h
作用：萃取迭代器类型
*************************************************************/

#ifndef ITERATOR_H
#define ITERATOR_H
#include<cstddef> //为了使用ptrdiff_t(一个与机器相关的数据类型，ptrdiff_t类型变量通常用来保存两个指针减法操作的结果)
namespace TinySTL {
	/*
	一、
		template<class T>
		void display_category(T itr)
		{
			typename iterator_traits<T>::iterator_category  cagy;
			__display_category(cagy); 这就是为何使用struct而不使用12345来做标志（能够重载）。
		}
	二、
		对算法的影响
		参考下方distance算法
	*/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//input_iterator
	template<class T, class Distance>
	struct input_iterator {
		typedef input_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance	difference_type;
		typedef T*	pointer;
		typedef T&	reference;
	};

	//output_iterator
	template <class T, class Distance>
	struct output_iterator {
		typedef output_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance	difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	//forward_iterator
	template <class T, class Distance>
	struct forward_iterator {
		typedef forward_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance	difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	//bidirectional_iterator
	template <class T, class Distance>
	struct bidirectional_iterator {
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance	difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	//random_access_iterator
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
		struct iterator {
		typedef Category		iterator_catagory;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
	};

	//萃取迭代器特性
	//这个模板为迭代器的类型特性定义了一套标准的类型别名，让算法既可以用迭代器，也可以用一般的指针
	template<typename Iterator>
	struct iterator_traits {
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
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef ptrdiff_t	difference_type;
		typedef T*	pointer;
		typedef T&	reference;
	};

	template<typename T>
	struct iterator_traits<const T*> {
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
	inline typename iterator_traits<Iterator>::value_type
		value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//计算迭代器之间的距离
	template<class _InIt>
	typename iterator_traits<_InIt>::difference_type
		distance(_InIt _First, _InIt _Last) 
	{
		return Pstar_distance(_First, _Last, iterator_category(_First));
	}

	//distance的input_iterator_tag版本
	template<class _InIt>
	typename iterator_traits<_InIt>::difference_type
		Pstar_distance(_InIt _First, _InIt _Last, input_iterator_tag) 
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
		Pstar_distance(_RanIt _First, _RanIt _Last,
			random_access_iterator_tag)
	{	/*如果不是iterator种类不是random类型，假设是farward，则会调用上面的input版本，因为farward继承自input*/
		return (_Last - _First);
	}

	//迭代器前进算法
	template<class _InIt, class _Distance>
	inline void advance(_InIt& i, _Distance n)
	{
		Pstar_advance(i, n, iterator_category(i));
	}

	template<class _InIt, class _Distance>
	inline void Pstar_advance(_InIt& i, _Distance n, input_iterator_tag)
	{
		while (n--) ++i;
	}

	template<class _InIt, class _Distance>
	inline void Pstar_advance(_InIt& i, _Distance n, bidirectional_iterator_tag)
	{
		if (n >= 0)
			while (n--)++i;
		else
			while (n++)--i;
	}
	
	template<class _InIt, class _Distance>
	inline void Pstar_advance(_InIt& i, _Distance n, random_access_iterator_tag)
	{
		i += n;
	}

	//**********************************************************************************
	//reverse_iterator
	template<class Iterator>
	class reverse_iterator {
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef const pointer const_pointer;
		typedef const reference const_reference;

	protected:
		typedef Iterator 
	};

} //namespace TinySTL
#endif // !ITERATOR_H