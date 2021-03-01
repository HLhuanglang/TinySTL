#include "container/string.h"

void String_test() {
  TinySTL::String s1("");
  TinySTL::String s2(" ");
  TinySTL::String s3("123456");
  s2 = s3;
  s1 = s3;
  TinySTL::String s4 = s3;
}