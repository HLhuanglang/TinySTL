#ifndef STRING_H_
#define STRING_H_
#include <string.h>

#include <string>

#include "fundation/allocator.h"
#include "fundation/iterator.h"

namespace TinySTL {
// basic_string
// 参考gcc、msvc

// CharType：要存储在字符串中的单个字符的数据类型
// Traits：描述了 basic_string 特殊化中元素的各种重要属性 Traits
// Allocator：内存分配器类型（此类的方法都是static）
template <typename CharType, typename Traits = std::char_traits<CharType>,
          typename Allocator = TinySTL::allocator<CharType>>
class basic_string {
 public:
  // typedef重命名，typename声明为类型
  using traits_type = Traits;
  using allocator_type = Allocator;

  using value_type = CharType;
  using size_type = typename allocator_type::size_type;
  using difference_type = typename allocator_type::difference_type;
  using pointer = typename allocator_type::pointer;
  using const_pointer = typename allocator_type::const_pointer;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = CharType*;
  using const_iterator = const CharType*;

  using reverse_iterator = TinySTL::reverse_iterator<iterator>;
  using const_reverse_iterator = TinySTL::reverse_iterator<const_iterator>;

  static const size_t npos = -1;

 public:
  // 成员函数
  basic_string<CharType, Traits, Allocator>& append(const value_type* ptr);
  basic_string<CharType, Traits, Allocator>& append(const value_type* ptr,
                                                    size_type count);
  basic_string<CharType, Traits, Allocator>& append(
      const basic_string<CharType, Traits, Allocator>& str, size_type offset,
      size_type count);
  basic_string<CharType, Traits, Allocator>& append(
      const basic_string<CharType, Traits, Allocator>& str);
  basic_string<CharType, Traits, Allocator>& append(size_type count,
                                                    value_type char_value);
  template <typename InputIterator>
  basic_string<CharType, Traits, Allocator>& append(InputIterator first,
                                                    InputIterator last);
  basic_string<CharType, Traits, Allocator>& append(const_pointer first,
                                                    const_pointer last);
  basic_string<CharType, Traits, Allocator>& append(const_iterator first,
                                                    const_iterator last);

  basic_string<CharType, Traits, Allocator>& assign(const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& assign(const value_type* ptr,
                                                    size_type count);

  basic_string<CharType, Traits, Allocator>& assign(
      const basic_string<CharType, Traits, Allocator>& str, size_type off,
      size_type count);

  basic_string<CharType, Traits, Allocator>& assign(
      const basic_string<CharType, Traits, Allocator>& str);

  basic_string<CharType, Traits, Allocator>& assign(size_type count,
                                                    value_type char_value);

  template <typename InIt>
  basic_string<CharType, Traits, Allocator>& assign(InIt first, InIt last);

  basic_string<CharType, Traits, Allocator>& assign(const_pointer first,
                                                    const_pointer last);

  basic_string<CharType, Traits, Allocator>& assign(const_iterator first,
                                                    const_iterator last);

  const_reference at(size_type offset) const;

  reference at(size_type offset);

  const_reference back() const;

  reference back();

  const_iterator begin() const;

  iterator begin();

  const value_type* c_str() const;

  size_type capacity() const;

  const_iterator cbegin() const;

  const_iterator cend() const;

  void clear();

  int compare(const basic_string<CharType, Traits, Allocator>& str) const;

  int compare(size_type position_1, size_type number_1,
              const basic_string<CharType, Traits, Allocator>& str) const;

  int compare(size_type position_1, size_type number_1,
              const basic_string<CharType, Traits, Allocator>& str,
              size_type offset, size_type count) const;

  int compare(const value_type* ptr) const;

  int compare(size_type position_1, size_type number_1,
              const value_type* ptr) const;

  int compare(size_type position_1, size_type number_1,
              const value_type* ptr size_type number_2) const;

  size_type copy(value_type* ptr, size_type count, size_type offset = 0) const;

  const_reverse_iterator crbegin() const;

  const_reverse_iterator crend() const;

  size_type _Copy_s(value_type* dest, size_type dest_size, size_type count,
                    size_type offset = 0) const;

  const value_type* data() const noexcept;
  value_type* data() noexcept;

  bool empty() const;

  const_iterator end() const;

  iterator end();

  iterator erase(iterator first, iterator last);

  iterator erase(iterator iter);

  basic_string<CharType, Traits, Allocator>& erase(size_type offset = 0,
                                                   size_type count = npos);

  size_type find(value_type char_value, size_type offset = 0) const;

  size_type find(const value_type* ptr, size_type offset = 0) const;

  size_type find(const value_type* ptr, size_type offset,
                 size_type count) const;

  size_type find(const basic_string<CharType, Traits, Allocator>& str,
                 size_type offset = 0) const;

  size_type find_first_not_of(value_type char_value,
                              size_type offset = 0) const;

  size_type find_first_not_of(const value_type* ptr,
                              size_type offset = 0) const;

  size_type find_first_not_of(const value_type* ptr, size_type offset,
                              size_type count) const;

  size_type find_first_not_of(
      const basic_string<CharType, Traits, Allocator>& str,
      size_type offset = 0) const;

  size_type find_first_of(value_type char_value, size_type offset = 0) const;

  size_type find_first_of(const value_type* ptr, size_type offset = 0) const;

  size_type find_first_of(const value_type* ptr, size_type offset,
                          size_type count) const;

  size_type find_first_of(const basic_string<CharType, Traits, Allocator>& str,
                          size_type offset = 0) const;

  size_type find_last_not_of(value_type char_value,
                             size_type offset = npos) const;

  size_type find_last_not_of(const value_type* ptr,
                             size_type offset = npos) const;

  size_type find_last_not_of(const value_type* ptr, size_type offset,
                             size_type count) const;

  size_type find_last_not_of(
      const basic_string<CharType, Traits, Allocator>& str,
      size_type offset = npos) const;

  size_type find_last_of(value_type char_value, size_type offset = npos) const;

  size_type find_last_of(const value_type* ptr, size_type offset = npos) const;

  size_type find_last_of(const value_type* ptr, size_type offset,
                         size_type count) const;

  size_type find_last_of(const basic_string<CharType, Traits, Allocator>& str,
                         size_type offset = npos) const;

  const_reference front() const;

  reference front();

  basic_string<CharType, Traits, Allocator>& insert(size_type position,
                                                    const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& insert(size_type position,
                                                    const value_type* ptr,
                                                    size_type count);

  basic_string<CharType, Traits, Allocator>& insert(
      size_type position, const basic_string<CharType, Traits, Allocator>& str);

  basic_string<CharType, Traits, Allocator>& insert(
      size_type position, const basic_string<CharType, Traits, Allocator>& str,
      size_type offset, size_type count);

  basic_string<CharType, Traits, Allocator>& insert(size_type position,
                                                    size_type count,
                                                    value_type char_value);

  iterator insert(iterator iter);

  iterator insert(iterator iter, value_type char_value);

  template <typename InputIterator>
  void insert(iterator iter, InputIterator first, InputIterator last);

  void insert(iterator iter, size_type count, value_type char_value);

  void insert(iterator iter, const_pointer first, const_pointer last);

  void insert(iterator iter, const_iterator first, const_iterator last);

  size_type length() const;

  size_type max_size() const;

  void pop_back();

  void push_back(value_type char_value);

  const_reverse_iterator rbegin() const;

  reverse_iterator rbegin();

  const_reverse_iterator rend() const;

  reverse_iterator rend();

  basic_string<CharType, Traits, Allocator>& replace(size_type position_1,
                                                     size_type number_1,
                                                     const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& replace(
      size_type position_1, size_type number_1,
      const basic_string<CharType, Traits, Allocator>& str);

  basic_string<CharType, Traits, Allocator>& replace(size_type position_1,
                                                     size_type number_1,
                                                     const value_type* ptr,
                                                     size_type number_2);

  basic_string<CharType, Traits, Allocator>& replace(
      size_type position_1, size_type number_1,
      const basic_string<CharType, Traits, Allocator>& str,
      size_type position_2, size_type number_2);

  basic_string<CharType, Traits, Allocator>& replace(size_type position_1,
                                                     size_type number_1,
                                                     size_type count,
                                                     value_type char_value);

  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& replace(
      iterator first0, iterator last0,
      const basic_string<CharType, Traits, Allocator>& str);

  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     const value_type* ptr,
                                                     size_type number_2);

  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     size_type number_2,
                                                     value_type char_value);

  template <typename InputIterator>
  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     InputIterator first,
                                                     InputIterator last);

  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     const_pointer first,
                                                     const_pointer last);

  basic_string<CharType, Traits, Allocator>& replace(iterator first0,
                                                     iterator last0,
                                                     const_iterator first,
                                                     const_iterator last);

  void reserve(size_type count = 0);

  void resize(size_type count, );

  void resize(size_type count, value_type char_value);

  size_type rfind(value_type char_value, size_type offset = npos) const;

  size_type rfind(const value_type* ptr, size_type offset = npos) const;

  size_type rfind(const value_type* ptr, size_type offset,
                  size_type count) const;

  size_type rfind(const basic_string<CharType, Traits, Allocator>& str,
                  size_type offset = npos) const;

  void shrink_to_fit();

  size_type size() const;

  basic_string<CharType, Traits, Allocator> substr(
      size_type offset = 0, size_type count = npos) const;

  void swap(basic_string<CharType, Traits, Allocator>& str);

  // 运算符
  basic_string<CharType, Traits, Allocator>& operator+=(value_type char_value);
  basic_string<CharType, Traits, Allocator>& operator+=(const value_type* ptr);
  basic_string<CharType, Traits, Allocator>& operator+=(
      const basic_string<CharType, Traits, Allocator>& right);

  basic_string<CharType, Traits, Allocator>& operator=(value_type char_value);
  basic_string<CharType, Traits, Allocator>& operator=(const value_type* ptr);
  basic_string<CharType, Traits, Allocator>& operator=(
      const basic_string<CharType, Traits, Allocator>& right);
  basic_string<CharType, Traits, Allocator>& operator=(
      const basic_string<CharType, Traits, Allocator>&& right);

  const_reference operator[](size_type offset) const;
  reference operator[](size_type offset);
};

class String {
 public:
  String();
  String(const char*);
  String(const String&);
  // todo:各种构造函数
  String(const char*, size_t);
  String(String&&);
  ~String();
  String& operator=(const String&);

 private:
  static const size_t npos = -1;  //结束标志位
  size_t size_;
  size_t capacity_;  //容器最大容量
  char* buffer_;
  TinySTL::allocator<char> alloc_;
};

String::String() : size_(0), capacity_(0), buffer_(nullptr) {}

String::String(const char* val) {
  if (val == "") {
    this->buffer_ = nullptr;
    this->size_ = 0;
    this->capacity_ = 0;
  } else {
    this->size_ = strlen(val);                     //计算空间
    this->buffer_ = alloc_.allocate(this->size_);  //申请空间
    strcpy(this->buffer_, val);                    //拷贝内容
    this->capacity_ = this->size_;
  }
}

String::String(const String& rhs) {
  this->buffer_ = this->alloc_.allocate(rhs.size_);
  strcpy(this->buffer_, rhs.buffer_);
  this->size_ = rhs.size_;
}

String::String(String&& rhs) {
  //转移
  this->buffer_ = rhs.buffer_;
  this->capacity_ = rhs.capacity_;
  this->size_ = rhs.size_;
  //释放
  delete[] rhs.buffer_;
  rhs.buffer_ = nullptr;
  rhs.buffer_ = 0;
  rhs.capacity_ = 0;
}

String::~String() {
  if (this->buffer_ != nullptr) {
    this->alloc_.deallocate(this->buffer_);
  }
  this->size_ = 0;
  this->capacity_ = 0;
}

String& String::operator=(const String& rhs) {
  this->buffer_ = this->alloc_.allocate(rhs.size_);
  strcpy(this->buffer_, rhs.buffer_);
  this->size_ = rhs.size_;
  this->capacity_ = rhs.capacity_;
  return *this;
}
}  // namespace TinySTL

#endif
