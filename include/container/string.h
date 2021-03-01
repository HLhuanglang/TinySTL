#ifndef STRING_H_
#define STRING_H_
#include <string.h>

#include "fundation/allocator.h"

namespace TinySTL {
// basic_string
// 参考gcc
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
