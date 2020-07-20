/*********************************************************************
模块名		: 通用
文件名		: exceptdef.h
相关文件		: 无
文件实现功能	: 提供参数描述宏、
作者			: HLhuanglang
版本			: 1.0
---------------------------------------------------------------------
备注			: 
---------------------------------------------------------------------
修改记录		:
日 期		版本		修改人			修改内容
2020/04/27	1.0     HLhuanglang		创建
********************************************************************/
#ifndef EXCEPTDEF_H
#define EXCEPTDEF_H

#include<stdexcept> //标准库的异常类
#include<cassert> //断言

namespace TinySTL {

#define STL_DEBUG(expr)	 assert(expr)

#define IN		/*输入参数*/
#define OUT		/*输出参数*/
#define DUMMY	/*哑元参数，仅帮助重载*/
#define FUNC	/*函数对象*/

} //namespace TinySTL
#endif // !EXCEPTDEF_H

