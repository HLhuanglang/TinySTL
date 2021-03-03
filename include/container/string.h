#ifndef STRING_H_
#define STRING_H_
#include <string.h>

#include <initializer_list>

#include "fundation/allocator.h"
#include "fundation/initializer_list.h"
#include "fundation/iterator.h"

namespace TinySTL {
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
  // 构造、析构
  basic_string() : size_(0), capacity_(0), buffer_(nullptr) {
    //这样写没什么依据...
    this->capacity_ = 15;
    this->buffer_ = new CharType[15];
  }

  basic_string(size_type count, CharType val,
               const Allocator& alloc = Allocator()) {
    this->size_ = count;
    this->capacity_ = count;
    // allocate分配内存是以8的倍数分配的,当count刚好是8的倍数时,就会导致内存溢出
    // 因为字符串总是以\0结尾的,默认时要多一个1字节的
    this->buffer_ = alloc.allocate(count + 1);
    for (int i = 0; i < count; i++) {
      this->buffer_[i] = val;
    }
    this->buffer_[count] = '\0';
  }

  // count,截取str里面多少个内容
  // s("12345",3) => s为123
  basic_string(const CharType* str, size_type count,
               const Allocator& alloc = Allocator()) {
    if (strlen(str) < count) {
      this->size_ = strlen(str);
      this->capacity_ = count;
      this->buffer_ = alloc.allocate(count + 1);
      strcpy(this->buffer_, str);
    } else {
      this->size_ = count;
      this->capacity_ = count;
      this->buffer_ = alloc.allocate(count + 1);
      for (int i = 0; i < count; i++) {
        this->buffer_[i] = str[i];
      }
      this->buffer_[count] = '\0';
    }
  }

  basic_string(const CharType* s, const Allocator& alloc = Allocator()) {
    this->size_ = strlen(s);
    this->buffer_ = alloc.allocate(this->size_ + 1);
    this->buffer_ =
        strcpy(this->buffer_, s);  //调用strcpy会多加一个 \0 表示结束
    this->capacity_ = this->size_;
  }

  basic_string(const basic_string& other,
               const Allocator& alloc = Allocator()) {
    this->buffer_ =
        alloc.allocate(other.capacity_);  //这里不用+1,因为other是一个合法的对象
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    strcpy(this->buffer_, other.buffer_);
  }

  basic_string(const basic_string& other, size_type pos, size_type count = npos,
               const Allocator& alloc = Allocator()) {
    this->size_ = other.size() - pos;
    this->capacity_ = this->size_;
    this->buffer_ = alloc.allocate(this->size_ + 1);
    for (int i = pos, j = 0; i < other.size_; i++, j++) {
      this->buffer_[j] = other.buffer_[i];
    }
    this->buffer_[this->size_] = '\0';
  }

  // std::string  s({'1', '2', '3', '4', '5'}); s为12345
  basic_string(std::initializer_list<CharType> ilist,
               const Allocator& alloc = Allocator()) {
    // todo
  }

  // std::string  s({'a', 'b', 'c', 'd', 'e'}, 3); s为de
  basic_string(std::initializer_list<CharType> ilist, size_type pos,
               const Allocator& alloc = Allocator()) {
    //需要把这个initializer_list对象绑定成basic_string,暂时不知道有什么好方法
    basic_string temp_bs;
    size_t ilist_size = ilist.size();
    CharType* temp_buf = new CharType[ilist_size + 1];
    int i = 0;
    // typename std::initializer_list<CharType>::iterator iter;
    // for (iter = ilist.begin(); iter != ilist.end(); ++iter, ++i) {
    //  temp_buf[i] = *iter;
    //}

    for (auto iter : ilist) {
      temp_buf[i] = iter;
      i++;
    }
    temp_buf[ilist_size] = '\0';
    temp_bs.size_ = ilist_size;
    temp_bs.buffer_ = temp_buf;
    // https://www.cnblogs.com/chio/archive/2007/10/20/931043.html
    new (this) basic_string(temp_bs, pos);
  }

  ~basic_string() {
    if (this->buffer_ != nullptr && this->size_ != 0) {
      delete[] this->buffer_;
      this->buffer_ = nullptr;
    }
    this->size_ = 0;
    this->capacity_ = 0;
  }

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

  const_reference at(size_type offset) const;

  reference at(size_type offset);

  const_reference back() const;

  reference back();

  const_iterator begin() const;

  iterator begin();

  const value_type* c_str() const;

  size_type count() const;

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

  int compare(size_type position_1, size_type number_1, const value_type* ptr,
              size_type number_2) const;

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

  void reserve(size_type count = 0);

  void resize(size_type count);

  void resize(size_type count, value_type char_value);

  size_type rfind(value_type char_value, size_type offset = npos) const;

  size_type rfind(const value_type* ptr, size_type offset = npos) const;

  size_type rfind(const value_type* ptr, size_type offset,
                  size_type count) const;

  size_type rfind(const basic_string<CharType, Traits, Allocator>& str,
                  size_type offset = npos) const;

  void shrink_to_fit();

  size_type size() const { return this->size_; }

  basic_string<CharType, Traits, Allocator> substr(
      size_type offset = 0, size_type count = npos) const;

  void swap(basic_string<CharType, Traits, Allocator>& str);

  // 运算符
  basic_string<CharType, Traits, Allocator>& operator+=(value_type char_value) {
    //暂时这样写，需要考虑边界问题
    this->buffer_[this->size_] = char_value;
    this->buffer_[this->size_ + 1] = '\0';
    this->size_ += 1;

    return *this;
  }

  basic_string<CharType, Traits, Allocator>& operator+=(const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& operator+=(
      const basic_string<CharType, Traits, Allocator>& right);

  basic_string<CharType, Traits, Allocator>& operator=(value_type char_value);

  basic_string<CharType, Traits, Allocator>& operator=(const value_type* ptr);

  basic_string<CharType, Traits, Allocator>& operator=(
      const basic_string<CharType, Traits, Allocator>& right) {}

  basic_string<CharType, Traits, Allocator>& operator=(
      const basic_string<CharType, Traits, Allocator>&& right) {}

  const_reference operator[](size_type offset) const;
  reference operator[](size_type offset);

 private:
  size_type size_;
  size_type capacity_;
  CharType* buffer_;
};

using String = basic_string<char>;
}  // namespace TinySTL

#endif
