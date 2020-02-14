/*********************************************************
���ƣ�uninitialized.h
���ã��ṩ�ڴ洦���ߺ���
ע�⣺
	�ٴ����first��last�����βΣ����Զ����ǽ����ƶ���Ӱ��
**********************************************************/
#ifndef UNINITIALIZED_H
#define UNINITIALIZED_H

#include"type_traits.h"
#include"construct.h"
#include"iterator.h"

#include<cstring>
namespace TinySTL {
	/*****************************************************
	���ƣ�uninitialized_copy
	���ã���[first,last) ���Ƶ�[result��result+(last-first) ),���ظ��ƽ�����λ��
	*****************************************************/
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first,InputIterator last,
		ForwardIterator result, __true_type){
			//��ʱ�����������ʹ��copy����
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}

	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, __false_type) {
		int i = 0;
		for (; first != last; ++first, ++i) {
			construct((result + i), *first);
		}
		return (result + i);
	}

	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
		typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type		IS_POD_TYPE;
		return _uninitialized_copy_aux(first, last, result, IS_POD_TYPE());
	}


	/***********************************************************************
	���ƣ�uninitialized_fill
	���ã��Ը����ķ�Χ[first��last)����ֵΪx���ж�����,�޷���ֵ
	************************************************************************/
	template<typename ForwardIterator,typename T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __true_type) {
		//����ʹ��fill�㷨�����滻
		TinySTL::fill(first, last, value);
	}
	template<typename ForwardIterator, typename T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __false_type) {
		for (; first != last; ++first)
			TinySTL::construct(first, value);
	}

	template<typename ForwardIterator, typename T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
		typedef typename __type_traits<T>::is_POD_type		IS_POD_TYPE;
			_uninitialized_fill_aux(first, last, value, IS_POD_TYPE());
	}


	/**********************************************************************
	���ƣ�uninitialized_fill_n
	���ã���[first��first+n*sizeof(T)����Χ�ڽ���n����ͬ����Ĺ��죬������������λ��
	***********************************************************************/
	template<typename ForwardIterator, typename Size,typename T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __true_type) {
		return TinySTL::fill_n(first, n, value);
 	}

	template<typename ForwardIterator , typename Size, typename T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __false_type) {
		int i = 0;
		for (; i != n; ++i) {
			construct((T*)(first + i), value);
		}
		return (first + i);
	}

	template<typename ForwardIterator, typename Size, typename T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& value) {
		typedef typename __type_traits<iterator_traits<ForwardIterator>::value_type>::is_POD_type		IS_POD_TYPE;
		return _uninitialized_fill_n_aux(first, n, value, IS_POD_TYPE());
	}

} //namespace TinySTL
#endif // !UNINITIALIZED_H
