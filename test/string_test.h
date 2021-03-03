#include <string>

#include "container/string.h"

void String_test() {
  std::string s({'1', '2', '3', '4', '5'}, 3);
  std::string s0({'1', '2', '3', '4', '5'});

  //在s1_执行完成后,s1的值会变成a(16)b(15)
  TinySTL::String s1(16, 'a');
  TinySTL::String s1_(15, 'b');

  TinySTL::String s2("1234", 3);

  TinySTL::String s4("123456789abcedfg");
  TinySTL::String s5("a23456789abcedfg");
  TinySTL::String S6({'1', '2', '3', '4'}, 2);
  TinySTL::String S7({'1', '2', '3', '4'}, 2);
}