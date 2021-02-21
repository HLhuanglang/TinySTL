#ifndef VECTOR_H
#define VECTOR_H

#include "algorithm/algorithm.h"
#include "fundation/allocator.h"
#include "fundation/iterator.h"
#include "fundation/uninitialized.h"

namespace TinySTL {
template <typename T>
class vector {
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
  iterator Iter_first;  //用三个迭代器来定位一个vector
  iterator Iter_last;
  iterator Iter_end;
  using data_allocator = TinySTL::allocator<T>;

 public:
  //==================================================================[[对象创建
  vector();
  explicit vector(const size_type _Nsize);
  vector(const size_type _Nsize, const value_type& _Val);
  template <typename InIt>
  vector(InIt _First, InIt _Last);
  vector(const vector& v);
  vector(vector&& v);
  vector& operator=(const vector& v);
  vector& operator=(vector&& v);
  ~vector();
  //==================================================================]]对象创建

  //==================================================================[[迭代器
  iterator begin() noexcept { return Iter_first; }
  const_iterator begin() const noexcept { return Iter_first; }
  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  const_iterator cbegin() const noexcept { return begin(); }
  const_reverse_iterator crbegin() const noexcept { return rbegin(); }
  iterator end() noexcept { return Iter_last; }
  const_iterator end() const noexcept { return Iter_last; }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(end());
  }
  const_iterator cend() const noexcept { return end(); }
  const_reverse_iterator crend() const noexcept { return rend(); }
  //==================================================================]]迭代器

  //==================================================================[[容量
  size_type size() const noexcept;
  bool empty() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  void reserve(size_type _Newcapacity);
  void resize(size_type _Size);
  void resize(size_type _Size, const value_type& _Val);
  void shrink_to_fit();
  //==================================================================]]容量

  //==================================================================[[赋值、存取
  void assign(size_type _Size, const value_type& _Val);
  template <class InIt>
  void assign(InIt _First, InIt _Last);
  void swap(vector& _Right) noexcept;
  reference at(size_type _Idx);
  const_reference at(size_type _Idx) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  void insert(iterator _Where, size_type _Count, value_type& _Val);
  template <class _InIt>
  void insert(iterator _Where, _InIt _First, _InIt _Last);
  iterator insert(iterator _Where, const value_type& _Val);
  void push_back(const value_type& _Val);
  void pop_back();
  iterator erase(const_iterator _Where);
  iterator erase(const_iterator _First, const_iterator _Last);
  void clear();

  //==================================================================[[赋值、存取

  //==================================================================[[其他
  data_allocator get_allocator() { return data_allocator; }
  //==================================================================]]其他

 private:
  /*vector helper function，begin with Pstar_ */
};  // end of class

//==================================================================[[运算符重载
template <class T>
bool operator==(const vector<T>& _Left, const vector<T>& _Right) {
  return _Left.size() == _Right.size() &&
         TinySTL::equal(_Left.begin(), _Left.end(), _Right.begin());
}

template <class T>
bool operator!=(const vector<T>& _Left, const vector<T>& _Right) {
  return !(_Left == _Right);
}

template <class T>
bool operator<(const vector<T>& _Left, const vector<T>& _Right) {
  return TinySTL::lexicographical_compare(_Left.begin(), _Left.end(),
                                          _Right.begin(), _Right.end());
}

template <class T>
bool operator>(const vector<T>& _Left, const vector<T>& _Right) {
  return _Right < _Left;
}

template <class T>
bool operator<=(const vector<T>& _Left, const vector<T>& _Right) {
  return !(_Right < _Left);  // A<=B -> !(A>B)
}

template <class T>
bool operator>=(const vector<T>& _Left, const vector<T>& _Right) {
  return !(_Left < _Right);
}
//==================================================================]]运算符重载

//==================================================================[[对象创建
template <class T>
vector<T>::vector() {
  Iter_first = data_allocator::allocate(1);
  Iter_last = Iter_first;
  Iter_end = Iter_first;
}

template <class T>
vector<T>::vector(const size_type _Nsize) {
  Iter_first = data_allocator::allocate(_Nsize);
  Iter_last = TinySTL::uninitialized_fill_n(Iter_first, _Nsize, value_type());
  Iter_end = Iter_last;
}

template <class T>
vector<T>::vector(const size_type _Nsize, const value_type& _Val) {
  Iter_first = data_allocator::allocate(_Nsize);
  Iter_last = TinySTL::uninitialized_fill_n(Iter_first, _Nsize, _Val);
  Iter_end = Iter_last;
}

template <class T>
template <class InIt>
vector<T>::vector(InIt _First, InIt _Last) {
  TinySTL::uninitialized_copy(_First, _Last, Iter_first);
}

template <class T>
vector<T>::vector(const vector& _Other) {
  size_t _Nsize = _Other.size();
  Iter_first = data_allocator::allocate(_Nsize);
  TinySTL::uninitialized_copy(_Other.begin(), _Other.end(), Iter_first);
}

template <class T>
vector<T>::vector(vector&& _Other) {
  Iter_first = _Other.Iter_first;
  Iter_last = _Other.Iter_last;
  Iter_end = _Other.Iter_end;
  _Other.Iter_first = nullptr;
  _Other.Iter_last = nullptr;
  _Other.Iter_end = nullptr;
}

template <class T>
vector<T>& vector<T>::operator=(IN const vector& rhs) {
  if (&rhs != this) { /*避免自赋值，通过判断地址来确定*/
    if (this->capacity < rhs.size()) {
      data_allocator::deallocate(this->Iter_first, this->size());
      TinySTL::destory(this->Iter_first, this->Iter_end);
      iterator _New_first = data_allocator::allocate(rhs.size());
      iterator _New_last = TinySTL::copy(rhs.begin(), rhs.end(), _New_first);
      this->Iter_first = _New_first;
      this->Iter_last = _New_last;
      this->Iter_end = _New_first + rhs.size();
    } else if (this->size() < rhs.size()) {
      TinySTL::vector<T> _Temp(rhs.begin(), rhs.end());
      swap(_Temp);
    } else {
      iterator _Temp_iter_last =
          TinySTL::copy(rhs.begin(), rhs.end(), this->Iter_first);
      TinySTL::destory(_Temp_iter_last, this->Iter_end);
    }
  }
  return *this;
}

template <class T>
vector<T>& vector<T>::operator=(vector&& _Other) {}

template <class T>
vector<T>::~vector() {
  TinySTL::destory(Iter_first, Iter_end);
  data_allocator::deallocate(Iter_first, Iter_end - Iter_first);
}

//==================================================================]]对象创建

template <class T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return static_cast<size_type>(Iter_last - Iter_first);
}

template <class T>
bool vector<T>::empty() const noexcept {
  return Iter_first == Iter_end;
}

template <class T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return static_cast<size_type>((-1) / sizeof(T));
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return Iter_end - Iter_first;
}

template <class T>
void vector<T>::reserve(size_type _Newcapacity) {
  if (_Newcapacity > this->capacity()) {
    iterator _New_first = data_allocator::allocate(_Newcapacity);
    iterator _New_last =
        TinySTL::uninitialized_copy(this->begin(), this->end(), _New_first);
    data_allocator::deallocate(this->Iter_first, this->size());
    TinySTL::destory(this->Iter_first, this->Iter_end);
    this->Iter_first = _New_first;
    this->Iter_last = _New_last;
    this->Iter_end = _New_first + _Newcapacity;
  }
  return;
}

template <class T>
void vector<T>::resize(size_type _Size) {}

template <class T>
void vector<T>::resize(size_type _Size, const value_type& _Val) {
  if (_Size < this->size()) {
  }
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (this->Iter_first == this->Iter_last) {
    return;
  } else {
    data_allocator::deallocate(this->Iter_last,
                               this->Iter_end - this->Iter_last);
    this->Iter_end = this->Iter_last;
  }
}

template <class T>
void vector<T>::assign(size_type _Size, const value_type& _Val) {}

template <typename T>
template <class InIt>
void vector<T>::assign(InIt _First, InIt _Last) {}

template <class T>
void vector<T>::swap(vector& _Right) noexcept {
  if (this != &_Right) {
    TinySTL::swap(Iter_first, _Right.Iter_first);
    TinySTL::swap(Iter_last, _Right.Iter_last);
    TinySTL::swap(Iter_end, _Right.end);
  }
}

//全局函数
template <class T>
void swap(vector<T>& _Left, vector<T>& _Right) {
  _Left.swap(_Right);
}
}  // namespace TinySTL
#endif  // !VECTOR_H
