#ifndef STRING_H_
#define STRING_H_

namespace TinySTL
{
class String {
 public:
  String();
  String(const char*);
  String(const String&);
  String(String&&);
  ~String();

  String& operator==(const String&);

 private:
  size_t size_;
  char* buffer_;
};

String::String() : size_(0), buffer_(nullptr) {}

}

#endif
