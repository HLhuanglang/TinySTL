#include <string>

#include "container/string.h"

void String_test() {
  auto s = std::string();
  s.size();

  TinySTL::String s1 = TinySTL::String("1234");

  TinySTL::String s2("123s");
  s2.~basic_string();
}