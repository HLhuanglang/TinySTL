#ifndef LIST_H
#define LIST_H

#include "fundation/allocator.h"
#include "fundation/exceptdef.h"
#include "fundation/functional.h"
#include "fundation/iterator.h"
#include "fundation/type_traits.h"
#include "fundation/utility.h"

namespace TinySTL {
template <class T>
class _List_node_base;
template <class T>
class _List_node;

/**********************************************************list������******************************************************/
template <class T>
class _List_node_base {
 public:
  typedef _List_node_base<T>* _Base_ptr;
  typedef _List_node<T>* _Node_ptr;

  //ָ����
  _Base_ptr _Prev;
  _Base_ptr _Next;

  _List_node_base() = default;

  _Base_ptr self() {  //�����_List_node_base����ĵ�ַ ת����һ��ָ�����͵ĵ�ַ
    return static_cast<_Base_ptr>(&*this);
  }
  void unlink() {  //�ս����βָ�붼ָ���Լ�
    _Prev = _Next = self();
  }
  _Node_ptr
  as_node() {  //����ָ��ת����������ָ�룬ʹ����Է��������������ĳ�Ա
    return static_cast<_Node_ptr>(self());
  }
};

template <class T>
class _List_node : public _List_node_base<T> {
 public:
  typedef _List_node_base<T>* _Base_ptr;
  typedef _List_node<T>* _Node_ptr;

  //ֵ��
  T _Myval;

  _List_node() = default;
  _List_node(const T& _Val) : _Myval(_Val) {}

  _Node_ptr self() { return static_cast<_Node_ptr>(&*this); }
  _Base_ptr as_base() {  //������ת���ɻ���ָ�룬ȥ����ָ��_Myval������
    return static_cast<_Base_ptr>(&*this);
  }
};

/**********************************************************list���������*****************************************************/
// const�������ͷ�const���������޷�ֱ����ǿ��ת��ʵ�֡���Ϊ�ڲ������ǲ�ͬ��

template <class T>
struct _List_iterator
    : public TinySTL::iterator<TinySTL::bidirectional_iterator_tag, T> {
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef _List_node_base<T>* _Base_ptr;
  typedef _List_node<T>* _Node_ptr;
  typedef _List_iterator<T> self;

  _Base_ptr _Node;  //ָ����

  //���캯��
  _List_iterator() = default;
  _List_iterator(_Base_ptr __Base_ptr) : _Node(__Base_ptr) {}
  _List_iterator(_Node_ptr __Node_ptr) : _Node(__Node_ptr->as_base()) {}
  _List_iterator(const _List_iterator<T>& rhs)
      : _Node(rhs._Node) {  //�������캯��
  }

  //���ز�����
  reference operator*() const { return _Node->as_node()->_Myval; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() {  //ǰ��++
    STL_DEBUG(_Node != nullptr);
    _Node = _Node->_Next;
    return *this;
  }

  self operator++(int) {  //����++
    self _Tmp = *this;
    ++*this;
    return _Tmp;
  }

  self& operator--() {
    STL_DEBUG(_Node != nullptr);
    _Node = _Node->_Prev;
    return *this;
  }

  self operator--(int) {
    self _Tmp = *this;
    --*this;
    return _Tmp;
  }

  //���رȽ������
  bool operator==(const self& rhs) const { return _Node == rhs._Node; }
  bool operator!=(const self& rhs) const { return _Node != rhs._Node; }
};

template <class T>
struct _List_const_iterator
    : public TinySTL::iterator<TinySTL::bidirectional_iterator_tag, T> {
  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef _List_node_base<T>* _Base_ptr;
  typedef _List_node<T>* _Node_ptr;
  typedef _List_const_iterator<T> self;

  _Base_ptr _Node;

  _List_const_iterator() = default;
  _List_const_iterator(_Base_ptr __Base_ptr) : _Node(__Base_ptr) {}
  _List_const_iterator(_Node_ptr __Node_ptr) : _Node(__Node_ptr->as_base()) {}
  _List_const_iterator(const _List_iterator<T>& rhs) : _Node(rhs._Node) {}

  _List_const_iterator(const _List_const_iterator<T>& rhs)
      : _Node(rhs._Node) {  //�������캯��
  }

  reference operator*() const { return _Node->as_node()->_Myval; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() {
    STL_DEBUG(_Node != nullptr);
    _Node = _Node->_Next;
    return *this;
  }

  self operator++(int) {
    self _Tmp = *this;
    ++*this;
    return _Tmp;
  }

  self& operator--() {
    STL_DEBUG(_Node != nullptr);
    _Node = _Node->_Prev;
    return *this;
  }

  self operator--(int) {
    self _Tmp = *this;
    --*this;
    return _Tmp;
  }

  // ���رȽϲ�����
  bool operator==(const self& rhs) const { return _Node == rhs._Node; }
  bool operator!=(const self& rhs) const { return _Node != rhs._Node; }
};

/**********************************************************list�����ṹ���******************************************************/
template <class T>
class list {
 public:
  typedef TinySTL::allocator<T>
      _Allocator_type;  //������ȡallocator��һЩ�ͱ���
  typedef TinySTL::allocator<T> _Data_allocator;  //�����ڽ���ֵ�� �������
  typedef TinySTL::allocator<_List_node<T>>
      _Node_allocator;  //���롢����_List_node���
  typedef TinySTL::allocator<_List_node_base<T>>
      _Base_allocator;  //���롢����_List_node_base���

  //��Ƕ�ͱ���
  typedef typename _Allocator_type::value_type value_type;
  typedef typename _Allocator_type::pointer pointer;
  typedef typename _Allocator_type::const_pointer const_pointer;
  typedef typename _Allocator_type::reference reference;
  typedef typename _Allocator_type::const_reference const_reference;
  typedef typename _Allocator_type::size_type size_type;
  typedef typename _Allocator_type::difference_type difference_type;

  //����������
  typedef _List_iterator<T> iterator;
  typedef _List_const_iterator<T> const_iterator;
  typedef TinySTL::reverse_iterator<iterator> reverse_iterator;
  typedef TinySTL::reverse_iterator<const_iterator> const_reverse_iterator;

  //�ڲ����ָ�붨��
  typedef _List_node_base<T>* _Base_ptr;
  typedef _List_node<T>* _Node_ptr;

 private:
  _Base_ptr _Node;  //ָ�� Ϊ������ǰ�պ�ԭ�����õĽ�� ��ָ��
  size_type _Size;  //���������

 private:
  // helper function

  //����������ٽ��
  _Node_ptr create_node(const value_type& _Val);
  void destory_node(_Node_ptr __Node_ptr);

  //��ʼ������
  void fill_init(size_type _Count, const value_type& _Val = value_type());
  template <class Iter>
  void copy_init(Iter fistr, Iter _Last);

  /*���빹��
  �����½��ʱ���������½���ѡ�����λ�ã���ͬλ�ò��뵼�����ӷ�ʽҲ��һ��
  �����Զ����½��ֵ��Ҳ���Ը���һ�����е�ֵ���н�㴴��
  */
  iterator link_one_node(const_iterator _Where, _Base_ptr __Base_ptr);
  void link_node(_Base_ptr __Base_ptr, _Base_ptr _First, _Base_ptr _Last);
  void link_node_at_front(_Base_ptr _First, _Base_ptr _Last);
  void link_node_at_back(_Base_ptr _First, _Base_ptr _Last);
  void unlink_node(_Base_ptr _First, _Base_ptr _Last);

  iterator fill_insert(const_iterator _Where, size_type _Count,
                       const value_type& _Val);
  template <class Iter>
  iterator copy_insert(const_iterator _Where, size_type _Count, Iter _First);

  template <class _InIt>
  void list_aux(_InIt _First, _InIt _Last, __false_type) {
    copy_init(_First, _Last);
  }
  void list_aux(size_type _Count, const value_type& _Val, __true_type) {
    fill_init(_Count, _Val);
  }
  template <class _InIt>
  void insert_aux(const_iterator _Where, _InIt _First, _InIt _Last,
                  __false_type) {
    size_type _Count = 0;
    auto _Tmp = _First;
    for (; _Tmp != _Last; ++_Tmp) _Count++;
    // distance����û�ã������Ľ��Ժ󻻳�distance
    copy_insert(_Where, _Count, _First);
  }
  void insert_aux(const_iterator _Where, size_type _Count,
                  const value_type& _Val, __true_type) {
    fill_insert(_Where, _Count, _Val);
  }

  void _splice_other(const_iterator _Where, list& _Right, const_iterator _First,
                     const_iterator _Last, size_type _Count);
  void _splice_self(const_iterator _Where, list& _Right, const_iterator _First,
                    const_iterator _Last, size_type _Count);

 public:
  /********************************************************************************/
  //�����졢�������
  list();
  list(size_type _Count);
  list(size_type _Count, const value_type& _Val);
  template <typename _InIt>
  list(_InIt _First, _InIt _Last);
  list(const list& _Right);
  ~list();

  /********************************************************************************/
  //���������
  iterator begin() { return _Node->_Next; }
  iterator end() { return _Node; }
  const_iterator begin() const { return _Node->_Next; }
  const_iterator end() const { return _Node; }

  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }

  /********************************************************************************/
  //����������
  bool empty() { return _Node->_Next == _Node; }
  size_type size() const { return _Size; }
  void resize(size_type _Newsize);
  void resize(size_type _Newsize, const value_type& _Val);

  /********************************************************************************/
  //Ԫ�ط������
  reference front() {
    STL_DEBUG(!empty());
    return *begin();
  }
  reference back() {
    STL_DEBUG(!empty());
    return *(--end());
  }

  /********************************************************************************/
  //Ԫ���޸�������
  void push_back(const value_type& _Val);
  void push_front(const value_type& _Val);
  void pop_back();
  void pop_front();

  iterator insert(iterator _Where, const value_type& _Val);
  void insert(iterator _Where, size_type _Count, const value_type& _Val);
  template <typename _InIt>
  void insert(iterator _Where, _InIt _First, _InIt _Last);

  void splice(const_iterator _Where, list& _Right);
  void splice(const_iterator _Where, list& _Right, const_iterator _First);
  void splice(const_iterator _Where, list& _Right, const_iterator _First,
              const_iterator _Last);

  iterator erase(const_iterator _Where);
  iterator erase(const_iterator _First, const_iterator _Last);

  void merge(list& _Right);
  template <typename Compare>
  void merge(list& _Right, Compare comp);

  void remove(const value_type& _Val);
  template <typename Predicate>
  void remove_if(Predicate pred);

  void unique();
  template <typename BinaryPredicate>
  void unique(BinaryPredicate _Pred);

  void clear();
  void reverse();
  void swap(list& _Right);
  void sort();
  template <typename Compare>
  void sort(Compare comp);
};  // end of  list class

/********************************************************************************/
// helper function ʵ��
template <class T>
typename list<T>::_Node_ptr list<T>::create_node(const value_type& _Val) {
  /*
  �������ܣ��Դ������Ϊֵ���������
  �������أ�����ָ��ý���ָ��
  */
  _Node_ptr __Node_ptr = _Node_allocator::allocate(1);
  _Data_allocator::construct(&__Node_ptr->_Myval, _Val);
  __Node_ptr->_Prev = nullptr;
  __Node_ptr->_Next = nullptr;
  return __Node_ptr;
}

template <class T>
void list<T>::destory_node(_Node_ptr __Node_ptr) {
  /*
  �������ܣ���������ָ����ָ��Ľ���ֵ��
  �������أ���
  */
  _Data_allocator::destory(&__Node_ptr->_Myval);
  _Node_allocator::deallocate(__Node_ptr);
}

template <class T>
void list<T>::fill_init(size_type _Count, const value_type& _Val) {
  /*
  �������ܣ���ʼ���������󣬴���_Count��ֵΪ_Val�Ľ��
  �������أ���
  */
  _Node = _Base_allocator::allocate(1);
  _Node->unlink();  //���ûд����Ԫ���_Node��ָ�����Ұָ��
  _Size = _Count;
  if (_Count == 0) return;
  for (; _Count > 0; --_Count) {
    _Node_ptr _New_node = create_node(_Val);
    link_node_at_back(_New_node->as_base(), _New_node->as_base());
  }
}

template <class T>
template <class Iter>
void list<T>::copy_init(Iter _First, Iter _Last) {
  /*
  �������ܣ���[_First,_Last)�����ڽ��ֵ��Ϊ�½���ֵ�����½��
  �������أ���
  */
  _Node = _Base_allocator::allocate(1);
  _Node->unlink();
  // auto _Tmp = _First;
  for (; _First != _Last; ++_First) {
    _Size++;
    _Node_ptr _New_node = create_node(*_First);
    link_node_at_back(_New_node->as_base(), _New_node->as_base());
  }
}

template <class T>
typename list<T>::iterator list<T>::link_one_node(const_iterator _Where,
                                                  _Base_ptr __Base_ptr) {
  /*
  �������ܣ���_Where������һ���½��__Base_ptr
  �������أ�����ָ���½��ĵ�����
  */
  if (_Where == _Node->_Next) {
    link_node_at_front(__Base_ptr, __Base_ptr);
  } else if (_Where == _Node) {
    link_node_at_back(__Base_ptr, __Base_ptr);
  } else
    link_node(_Where._Node, __Base_ptr, __Base_ptr);
  return __Base_ptr;
}

template <class T>
void list<T>::link_node(_Base_ptr __Base_ptr, _Base_ptr _First,
                        _Base_ptr _Last) {
  /*
  �������ܣ���__Base_ptr��������һ�ν��[_First,_Last)
  �������أ���
  */
  __Base_ptr->_Prev->_Next = _First;
  _Last->_Next = __Base_ptr;
  _First->_Prev = __Base_ptr->_Prev;
  __Base_ptr->_Prev = _Last;
}

template <class T>
void list<T>::link_node_at_front(_Base_ptr _First, _Base_ptr _Last) {
  /*
  �������ܣ�����Ԫ���_Node��������һ������[_First,_Last)
  �������أ���
  */
  _Last->_Next = _Node->_Next;
  _Node->_Next->_Prev = _Last;
  _First->_Prev = _Node;
  _Node->_Next = _First;
}

template <class T>
void list<T>::link_node_at_back(_Base_ptr _First, _Base_ptr _Last) {
  /*
  �������ܣ���_Nodeǰ����һ������[_First,_Last)
  �������أ���
  */
  _Last->_Next = _Node;
  _First->_Prev = _Node->_Prev;  //
  _First->_Prev->_Next =
      _First;  //���_Node֮ǰû�н�㣬�����������þ���_First=_First��
  _Node->_Prev = _Last;
}

template <class T>
void list<T>::unlink_node(_Base_ptr _First, _Base_ptr _Last) {
  /*
  �������ܣ���һ�ν��[_First,_Last)���������г�
  �������أ���
  */
  _First->_Prev->_Next = _Last->_Next;
  _Last->_Next->_Prev = _First->_Prev;
}

template <class T>
typename list<T>::iterator list<T>::fill_insert(const_iterator _Where,
                                                size_type _Count,
                                                const value_type& _Val) {
  /*
  �������ܣ�����insert����������_Count��ֵΪ_Val�Ľ�㣬������_Where֮��
  �������أ�����һ��ָ��������Ľ��ĵ�����
  */
  _Size += _Count;
  iterator r;
  for (; _Count > 0; _Count--) {
    _Node_ptr _New_node = create_node(_Val);
    r = link_one_node(_Where, _New_node->as_base());
  }
  return r;
}

template <class T>
template <class Iter>
typename list<T>::iterator list<T>::copy_insert(const_iterator _Where,
                                                size_type _Count, Iter _First) {
  /*
  �������ܣ�����insert����һ�ν��[_First,_First+_Count)��ֵΪ�½��ֵ�����½�㣬������_Where֮��
  �������أ�����һ��ָ������������Ľ��ĵ�����
  */
  size_type _Add_size = _Count;
  _Size += _Add_size;
  iterator r;
  for (; _Count > 0; _Count--, ++_First) {
    _Node_ptr _New_node = create_node(*_First);
    r = link_one_node(_Where, _New_node->as_base());
  }
  return r;
}

/********************************************************************************/
//�����졢�������
template <class T>
list<T>::list() {
  fill_init(0, value_type());
}

template <class T>
list<T>::list(size_type _Count) {
  fill_init(_Count, value_type());
}

template <class T>
list<T>::list(size_type _Count, const value_type& _Val) {
  typedef typename __is_integer<size_type>::is_integer IS_INTEGER;
  list_aux(_Count, _Val, IS_INTEGER());
}

template <class T>
template <class _InIt>
list<T>::list(_InIt _First, _InIt _Last) {
  typedef typename __is_integer<_InIt>::is_integer IS_INTEGER;
  list_aux(_First, _Last, IS_INTEGER());
}

template <class T>
list<T>::list(const list& _Right) {
  copy_init(_Right.cbegin(), _Right.cend());
}

template <class T>
list<T>::~list() {
  //��ͨ������Ԫ���ֿ�����
  if (_Node) {
    clear();
    _Base_allocator::deallocate(_Node);
    _Node = nullptr;
    _Size = 0;
  }
}

/********************************************************************************/
//����������
template <class T>
void list<T>::resize(size_type _Newsize) {
  resize(_Newsize, value_type());
}

template <class T>
void list<T>::resize(size_type _Newsize, const value_type& _Val) {
  if (_Newsize > size()) {
    size_type _Add_size = _Newsize - _Size;
    while (_Add_size--) push_back(_Val);
    _Size = _Newsize;
  } else {
    size_type _Delete_size = size() - _Newsize;
    while (_Delete_size--) pop_back();  //ע��pop_back����Ҳ���_Size���м�һ
    _Size = _Newsize;
  }
}

/********************************************************************************/
//Ԫ���޸�������
template <class T>
void list<T>::clear() {
  if (_Size != 0) {
    _Base_ptr cur = _Node->_Next;
    for (_Base_ptr _Next = cur->_Next; cur != _Node;
         cur = _Next, _Next = _Next->_Next) {
      destory_node(cur->as_node());
    }
  }
  //�����ϣ�ʣ����Ԫ���
  _Node->unlink();
  _Size = 0;
}

template <class T>
void list<T>::push_back(const value_type& _Val) {
  _Node_ptr _New_node = create_node(_Val);
  link_node_at_back(_New_node->as_base(), _New_node->as_base());
  _Size++;
}

template <class T>
void list<T>::push_front(const value_type& _Val) {
  _Node_ptr _New_node = create_node(_Val);
  link_node_at_front(_New_node->as_base(), _New_node->as_base());
  _Size++;
}

template <class T>
void list<T>::pop_back() {
  if (!empty()) {
    _Base_ptr _Tmp = _Node->_Prev;
    unlink_node(_Tmp, _Tmp);
    _Tmp->unlink();
    destory_node(_Tmp->as_node());
    _Size--;
  }
}

template <class T>
void list<T>::pop_front() {
  if (!empty()) {
    _Base_ptr _Tmp = _Node->_Next;
    unlink_node(_Tmp, _Tmp);
    _Tmp->unlink();
    destory_node(_Tmp->as_node());
    _Size--;
  }
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator _Where,
                                           const value_type& _Val) {
  _Node_ptr _New_node = create_node(_Val);
  _Size++;
  return link_one_node(_Where, _New_node->as_base());
}

template <class T>
void list<T>::insert(iterator _Where, size_type _Count,
                     const value_type& _Val) {
  typedef typename __is_integer<size_type>::is_integer IS_INTEGER;
  insert_aux(_Where, _Count, _Val, IS_INTEGER());
}

template <class T>
template <class _InIt>
void list<T>::insert(iterator _Where, _InIt _First, _InIt _Last) {
  typedef typename __is_integer<_InIt>::is_integer IS_INTEGER;
  insert_aux(_Where, _First, _Last, IS_INTEGER());
}

template <class T>
void list<T>::splice(const_iterator _Where, list& _Right) {
  /*
  �������ܣ�����������_Right�������������ϲ��������_Where֮ǰ�����Ӷ�ʽ�ϲ���
  �������أ���
  */
  STL_DEBUG(this != &_Right);
  if (!_Right.empty()) {
    // insert(_Where, _Right.begin(), _Right.end()); ��������Ӷ�ʽ����
    auto _First = _Right._Node->_Next;
    auto _Last = _Right._Node->_Prev;

    _Right.unlink_node(_First, _Last);
    link_node(_Where._Node, _First, _Last);

    _Size += _Right._Size;
    _Right._Size = 0;
  }
}

template <class T>
void list<T>::splice(const_iterator _Where, list& _Right,
                     const_iterator _First) {
  /*
  �������ܣ�������_Right[_First, _First+1���ϲ���_Where֮ǰ���Ӷ�ʽ�ϲ���
  �������أ���
  */
  if (_Where._Node != _First._Node && _Where._Node != _First._Node->_Next) {
    auto _Tmp = _First._Node;
    _Right.unlink_node(_Tmp, _Tmp);
    link_node(_Where._Node, _Tmp, _Tmp);
    ++_Size;
    --_Right._Size;
  }
}

template <class T>
void list<T>::splice(const_iterator _Where, list& _Right, const_iterator _First,
                     const_iterator _Last) {
  /*
  �������ܣ�������_Right��������������һ�ν��[_First��_Last)�ϲ���_Where֮ǰ�����Ӷ�ʽ�ϲ���
  �������أ���
  */
  size_type _Count = 0;
  auto _Tmp = _First;
  while (_Tmp != _Last) {
    _Tmp++;
    _Count++;
  }

  if (_First != _Last && this != &_Right) {
    auto _Tmp_first = _First._Node;
    auto _Tmp_last = _Last._Node->_Prev;

    _Right.unlink_node(_Tmp_first, _Tmp_last);
    link_node(_Where._Node, _Tmp_first, _Tmp_last);
    _Size += _Count;
    _Right._Size -= _Count;
  }
}

template <class T>
typename list<T>::iterator list<T>::erase(const_iterator _Where) {
  if (_Where != cend()) {
    _Base_ptr _Tmp = _Where._Node;
    _Base_ptr _Next = _Tmp->_Next;
    unlink_node(_Tmp, _Tmp);
    destory_node(_Tmp->as_node());
    --_Size;
    return iterator(_Next);
  }
}

template <class T>
typename list<T>::iterator list<T>::erase(const_iterator _First,
                                          const_iterator _Last) {
  for (; _First != _Last; ++_First) {
    erase(_First);
  }
  return _Last._Node;
}

template <class T>
void list<T>::merge(list& _Right) {
  merge(_Right, TinySTL::less<T>());
}

template <class T>
template <class Compare>
void list<T>::merge(list& _Right, Compare comp) {
  if (this != &_Right) {
    iterator _First1 = begin();
    iterator _Last1 = end();
    iterator _First2 = _Right.begin();
    iterator _Last2 = _Right.end();

    while (_First1 != _Last1 && _First2 != _Last2) {
      if (comp(*_First2, *_First1)) {
        //ʹ��compΪ��
        iterator _Next = _First2;
        ++_Next;
        for (; _Next != _Last2 && comp(*_Next, *_First1);
             ++_Next)  //��Ѱһ�������copmҪ��Ľ�㣬���Ч��
          ;
        auto _Tmp_first = _First2._Node;
        auto _Tmp_last = _Next._Node->_Prev;
        _First2 = _Next;

        // link node
        _Right.unlink_node(_Tmp_first, _Tmp_last);
        link_node(_First1._Node, _Tmp_first, _Tmp_last);
        ++_First1;
      } else {
        ++_First1;
      }
    }

    //����ʣ����
    if (_First2 != _Last2) {
      auto _Tmp_first = _First2._Node;
      auto _Tmp_last = _Last2._Node->_Prev;
      _Right.unlink_node(_Tmp_first, _Tmp_last);
      link_node(_First1._Node, _Tmp_first, _Tmp_last);
    }

    _Size += _Right._Size;
    _Right._Size = 0;
  }
}

template <class T>
void list<T>::remove(const value_type& _Val) {
  // lamada���ʽ
  remove_if([&](const value_type& _Tmp) { return _Tmp == _Val; });
}

template <class T>
template <class Predicate>
void list<T>::remove_if(Predicate _Pred) {
  auto _First = begin();
  auto _Last = end();
  for (auto _Next = _First; _First != _Last; _First = _Next) {
    // eraseÿ�ζ����ͷŴ���ĵ����������µ�����ʧЧ������ÿ��ѭ��_First=_Next
    ++_Next;
    if (_Pred(*_First)) erase(_First);  // erase����--_Size
  }
}

template <class T>
void list<T>::unique() {
  unique(TinySTL::equal_to<T>());
}

template <class T>
template <class BinaryPredicate>
void list<T>::unique(BinaryPredicate _Pred) {
  //�������ڣ���[ _Cur, _First ]Ϊ������ǰ�ƶ�������������ɾ��_Cur
  auto _First = begin();
  auto _Last = end();
  auto _Cur = _First;
  ++_First;
  while (_First != _Last) {
    if (_Pred(*_First, *_Cur))
      erase(_Cur);
    else {
      _Cur = _First;
    }
    _Cur = _First;
    ++_First;
  }
}

template <class T>
void list<T>::reverse() {
  if (_Size <= 1) return;
  iterator _First = begin();
  iterator _Last = end();
  while (_First._Node != _Last._Node) {
    TinySTL::swap(_First._Node->_Prev, _First._Node->_Next);
    _First = _First._Node->_Prev;
  }
  TinySTL::swap(_Last._Node->_Prev, _Last._Node->_Next);
}

template <class T>
void list<T>::swap(list& _Rigth) {
  //�����ڲ��ṹ����ָ����Ԫ�ڵ��ָ��
  TinySTL::swap(_Node, _Rigth._Node);
  TinySTL::swap(_Size, _Rigth._Size);
}

template <class T>
void list<T>::sort() {
  // TO DO
}

template <class T>
template <class Compare>
void list<T>::sort(Compare comp) {
  // TO DO
}
}  // namespace TinySTL
#endif  // !LIST_H
