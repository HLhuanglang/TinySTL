/************************************************************
���ƣ�exceptdef.h
���ã�����һЩ�쳣�ĺ꺯��
*************************************************************/

#ifndef EXCEPTDEF_H
#define EXCEPTDEF_H

#include<stdexcept> //��׼����쳣��
#include<cassert> //����

namespace TinySTL {

#define STL_DEBUG(expr)\
 assert(expr)

} //namespace TinySTL
#endif // !EXCEPTDEF_H

