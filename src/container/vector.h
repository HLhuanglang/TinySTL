/************************************************************
	名称：vector.h
	作用：vector容器类，用于实例化vector容器对象。
	使用：
		vector<T>	test
		test.xxx()  通过对象调用类中的方法
*************************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include"../fundation/allocator.h"
#include"../fundation/iterator.h"
#include"../fundation/utility.h"
#include"../fundation/uninitialized.h"
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

private:
	iterator Iter_first; //用三个迭代器来定位一个vector
	iterator Iter_last;
	iterator Iter_end;
	using data_allocator = TinySTL::allocator<T>;	//类的别名，用来直接访问静态方法

public:
	/*vector API manual*/
	//构造析构相关函数
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

	//迭代器相关函数
	iterator begin()  noexcept { return Iter_first; }
	const_iterator begin() const noexcept { return Iter_first; }
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	const_iterator cbegin() const noexcept { return begin(); }
	const_reverse_iterator crbegin() const noexcept { return rbegin(); }

	iterator end()  noexcept { return Iter_last; }
	const_iterator end() const noexcept { return Iter_last; }
	reverse_iterator rend()  noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const noexcept { return const_reverse_iterator(end()); }
	const_iterator cend() const noexcept { return end(); }
	const_reverse_iterator crend() const noexcept { return rend(); }
	
	//非变动性操作
	size_type size() const noexcept;
	bool empty()const noexcept;
	size_type max_size() const noexcept;
	size_type capacity() const noexcept;
	void reserve(size_type _Newcapacity);

	//赋值
	void assign(size_type _Size, const value_type& _Val);
	template<class InIt>
	void assign(InIt _First, InIt _Last);
	void swap(vector& _Right) noexcept;	//为何不用const vector& _Right

	//元素存取
	reference at(size_type _Idx);
	const_reference at(size_type _Idx) const;
		/*front,back不检查第一，最后一个元素是否存在*/
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	data_allocator get_allocator() { return data_allocator; }
private:
	/*vector helper function，begin with Pstar_ */



};//end of class



template<class T>
vector<T>::vector()
{
	Iter_first = data_allocator::allocate(1);	//这里是用通过类名:: 直接调用static方法。 data_allocator().allocate(1)这样是创建一个匿名对象来调用
	Iter_last = Iter_first;
	Iter_end = Iter_first;
}

template<class T>
vector<T>::vector(const size_type _Nsize) {
	Iter_first = data_allocator::allocate(_Nsize);
	Iter_last = TinySTL::uninitialized_fill_n(Iter_first, _Nsize, value_type());
	Iter_end = Iter_last;
}

template<class T>
vector<T>::vector(const size_type _Nsize, const value_type& _Val) {
	Iter_first = data_allocator::allocate(_Nsize);
	Iter_last = TinySTL::uninitialized_fill_n(Iter_first, _Nsize, _Val);
	Iter_end = Iter_last;
}

//template<class T>
//template<class InIt>
//vector<T>::vector(InIt _First, InIt _Last) {
//	TinySTL::uninitialized_copy(_First, _Last, Iter_first);
//}


template<class T>
vector<T>::~vector()
{
	TinySTL::destory(Iter_first, Iter_end);
	data_allocator::deallocate(Iter_first, Iter_end-Iter_first);
}


template<class T>
typename vector<T>::size_type vector<T>::size() const noexcept {
	return static_cast<size_type>(Iter_last - Iter_first);
}

template<class T>
bool vector<T>::empty() const noexcept {
	return Iter_first == Iter_end;
}

template<class T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
	return static_cast<size_type>((-1)/sizeof(T));
}




//重载操作符
//常量对象只能调用常函数（不对成员做出改动）
template<class T>
bool operator==(const vector<T>& _Left,const vector<T>& _Right) {
	return _Left.size() == _Right.size() &&
		TinySTL::equal(_Left.begin(), _Left.Iter_end(), _Right.begin());
}

template<class T>
bool operator!=(const vector<T>& _Left, const vector<T>& _Right) {
	return !(_Left == _Right);
}

template<class T>
bool operator<(const vector<T>& _Left, const vector<T>& _Right) {
	return TinySTL::lexicographical_compare(_Left.begin(), _Left.end(), _Right.begin(), _Right.end());
}

template<class T>
bool operator>(const vector<T>& _Left, const vector<T>& _Right) {
	return _Right < _Left;
}

template<class T>
bool operator<=(const vector<T>& _Left, const vector<T>& _Right) {
	return !(_Right < _Left);	//A<=B -> !(A>B)
}

template<class T>
bool operator>=(const vector<T>& _Left, const vector<T>& _Right) {
	return !(_Left < _Right);
}


}//namaspace TinySTL
#endif // !VECTOR_H
