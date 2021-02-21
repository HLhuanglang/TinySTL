#ifndef EXCEPTDEF_H
#define EXCEPTDEF_H

#include <cassert>    //断言
#include <stdexcept>  //标准库的异常类

namespace TinySTL {
#define STL_DEBUG(expr) assert(expr)

#define IN    /*输入参数*/
#define OUT   /*输出参数*/
#define DUMMY /*哑元参数，仅帮助重载*/
#define FUNC  /*函数对象*/
}  // namespace TinySTL
#endif  // !EXCEPTDEF_H
