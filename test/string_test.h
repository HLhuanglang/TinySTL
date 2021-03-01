#include <string>

#include "container/string.h"

TinySTL::String test_1() {
  TinySTL::String temp("123456789");
  return temp;
}

void String_test() {
  test_1();
  TinySTL::String s1("");
  s1.~String();
  TinySTL::String s2(" ");
  s2.~String();
  TinySTL::String s3("123456");
  TinySTL::String s4 = s3;
}