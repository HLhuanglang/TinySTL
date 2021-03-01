#ifndef STRING_H_
#define STRING_H_

#include <assert.h>

#include <iostream>

namespace TinySTL {
class String {
 public:
  String();
  String(const char*);
  String(const String&);
  String(String&&);
  ~String();
  String& operator=(const String&);

 private:
  size_t size_;
  size_t capacity_;  //ÈÝÆ÷×î´óÈÝÁ¿
  char* buffer_;
};

String::String() : size_(0), capacity_(0), buffer_(nullptr) {}

String::String(const char* val) {
  if (val == "") {
    this->buffer_ = nullptr;
    this->size_ = 0;
    this->capacity_ = 0;
  } else {
    buffer_ = const_cast<char*>(val);
    this->size_ = strlen(this->buffer_);
    this->capacity_ = this->size_;
  }
}

String::String(const String& rhs) {
  size_t new_size = rhs.size_;
  this->buffer_ = new char[new_size + 1];
  strcpy(this->buffer_, rhs.buffer_);
  this->size_ = rhs.size_;
}

String::String(String&& rhs) {
  this->buffer_ = rhs.buffer_;
  this->capacity_ = rhs.capacity_;
  this->size_ = rhs.size_;
  delete[] rhs.buffer_;
  rhs.buffer_ = nullptr;
  rhs.buffer_ = 0;
  rhs.capacity_ = 0;
}

String::~String() {
  if (this->buffer_ != nullptr) {
    delete[] this->buffer_;
  }
  this->size_ = 0;
  this->capacity_ = 0;
}

String& String::operator=(const String& rhs) {
  size_t new_size = rhs.size_;
  this->buffer_ = new char[new_size + 1];
  strcpy(this->buffer_, rhs.buffer_);
  this->size_ = rhs.size_;
  return *this;
}
}  // namespace TinySTL

#endif
