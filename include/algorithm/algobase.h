#ifndef ALGOBASE_H
#define ALGOBASE_H

#include <algorithm>

#include "fundation/exceptdef.h"
#include "fundation/type_traits.h"

namespace TinySTL {
/******************************************************
函 数 名：swap
函数作用：输入参数完全交换(给容器就交换容器,给容器内部元素就换元素)
函数参数：
                [IN]	_Left :交换对象
                [IN]	_Right:交换对象
返 回 值：无
******************************************************/
template <typename T>
void swap(IN T& _Left, IN T& _Right) {
  T _Temp = _Left;
  _Left = _Right;
  _Right = _Temp;
}

/******************************************************
函 数 名：max
函数作用：返回二者中更大的一方
函数参数：
                [IN]	_Left :比较对象
                [IN]	_Right:比较对象
                [FUNC]	_Pred :比较标准
返 回 值：二者中更大的一方
******************************************************/
template <class _Ty>
const _Ty& max(IN const _Ty& _Left, IN const _Ty& _Right) {
  return _Left < _Right ? _Right : _Left;
}

template <class _Ty, class _Pr>
const _Ty& max(IN const _Ty& _Left, IN const _Ty& _Right,
               FUNC _Pr _Pred) {  //由_Pred决定“大小比较”标准
  return (_Pred(_Left, _Right)) ? _Right : _Left;
}

/******************************************************
函 数 名：min
函数作用：返回二者中更小的一方
函数参数：
                [IN]	_Left :比较对象
                [IN]	_Right:比较对象
                [FUNC]	_Pred :比较标准
返 回 值：二者中更小的一方
******************************************************/
template <class _Ty>
const _Ty& min(IN const _Ty& _Left, IN const _Ty& _Right) {
  return _Right < _Left ? _Right : _Left;
}

template <class _Ty, class _Pr>
const _Ty& min(IN const _Ty& _Left, IN const _Ty& _Right,
               FUNC _Pr _Pred) {  //由_Pred决定“大小比较”标准
  return (_Pred(_Right, _Left)) ? _Right : _Left;
}

/******************************************************
函 数 名：iter_swap
函数作用：交换两个迭代器所指对象
函数参数：
                [IN]	_Left :迭代器对象
                [IN]	_Right:迭代器对象
返 回 值：无
******************************************************/
template <class _FwdIt1, class _FwdIt2>
inline void iter_swap(IN _FwdIt1 _Left, IN _FwdIt2 _Right) {
  swap(*_Left, *_Right);
}

/******************************************************
函 数 名：equal
函数作用：判断两个序列在[_First,_Last)区间相等
函数参数：
                [IN]	_First1:序列1区间起始地址
                [IN]	_Last1 :序列1区间结束地址
                [IN]	_First2:序列2区间起始地址
返 回 值：两序列相等，返回true；不相等返回false
注 意 点：第二序列元素个数 >= 第一序列
******************************************************/
template <class _InIt1, class _InIt2>
inline bool equal(IN _InIt1 _First1, IN _InIt1 _Last1, IN _InIt2 _First2) {
  for (; _First1 != _Last1;
       ++_First1, ++_First2) {  //如果第二序列更短，迭代时会造成不可预测的结果
    if (*_First1 != *_First2) return false;
  }
  return true;
}

/******************************************************
函 数 名：fill
函数作用：将[_First,_Last)内的所有元素改填新值
函数参数：
                [IN]	_First:目标区间起始地址
                [IN]	_Last :目标区间结束地址
                [IN]	_Val  :目标区间元素新值
返 回 值：无
******************************************************/
template <class _FwdIt, class _Ty>
void fill(IN _FwdIt _First, IN _FwdIt _Last, IN const _Ty& _Val) {
  for (; _First != _Last; ++_First) {
    *_First = _Val;
  }
}

/******************************************************
函 数 名：fill_n
函数作用：将区间[_First，_First+n）填充为新值
函数参数：
                [IN/OUT]_First:IN-目标区间起始地址,OUT-填充结束地址
                [IN]	_Count:填充元素个数
                [IN]	_Val  :填充元素值
返 回 值：填充结束处迭代器，即 _First+_Count处迭代器
******************************************************/
template <class _OutIt, class Size, class _Ty>
_OutIt fill_n(IN OUT _OutIt _First, IN Size _Count, IN const _Ty& _Val) {
  for (; _Count > 0; --_Count, ++_First) {
    *_First = _Val;
  }
  return _First;
}

/**************************************************************************
函 数 名：copy
函数作用：将[_First,_Last)复制到[_Result,_Result+(_Last-_First))区间
函数参数：
                [IN]	_First:源区间起始地址
                [IN]	_Last :源区间结束地址
                [IN/OUT]_Result:IN-新区间起始地址，OUT-新区间结束地址
返 回 值：返回新区间的结束位置处迭代器，即_Result+(_Last-_First)处迭代器
**************************************************************************/
template <class _InIt, class _OutIt>
_OutIt copy(IN _InIt _First, IN _InIt _Last, IN OUT _OutIt _Result) {
  return _copy(_First, _Last, _Result, value_type(_First));
}

template <class _InIt, class _OutIt, class T>
_OutIt _copy(_InIt _First, _InIt _Last, _OutIt _Result, T*) {
  typedef typename __type_traits<T>::is_POD_type IS_POD;
  return Pstar_copy(_First, _Last, _Result, IS_POD());
}

template <class _InIt, class _OutIt>
_OutIt Pstar_copy(_InIt _First, _InIt _Last, _OutIt _Result, __true_type) {
  auto _Dis = distance(_First, _Last);
  memcpy(_Result, _First, sizeof(*_First) * _Dis);
  advance(_Result, _Dis);
  return _Result;
}

template <class _InIt, class _OutIt>
_OutIt Pstar_copy(_InIt _First, _InIt _Last, _OutIt _Result, __false_type) {
  while (_First != _Last) {
    *_Result = *_First;
    _Result++;
    _First++;
  }
  return _Result;
}
/******************************************************
函 数 名：lexicographical_compare
函数作用：
        以“字典排列方式”对两个序列[_First1,_Last1)和[_First2,_Last2)进行比较。
        也就是第一序列以字典排列方式而言不小于第二序列。
函数说明：
        比较操作针对两序列中的对应位置上的元素进行，并持续到
        (1)某一组元素彼此不相等
        (2)同时到达_Last1和_Last2
        (3)到达_Last1或_Last2
        返 回 值：
        (1)如果第一序列的元素较小，返回true。否则返回false
        (2)如果到达_Last1而尚未到达_Last2，返回true
        (3)如果到达_Last2而尚未到达_Last1,返回false
        (4)如果同时到达_Last1和_Last2，返回false
******************************************************/
template <class _InIt1, class _InIt2>
bool lexicographical_compare(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2,
                             _InIt2 _Last2) {
  for (
      ; _First1 != _Last1 && _First2 != _Last2;
      ++_First1,
      ++_First2) {  //任何一个序列到达尾部，就结束。否则两序列就相对应一一进行对比
    if (*_First1 < *_First2) return true;
    if (*_First1 > *_First2) return false;
  }
  return _First1 == _Last1 &&
         _First2 != _Last2; /*第一序列到达尾部而第二序列尚有余额*/
}

//使用函数对象作为比较准则，进行重载
template <class _InIt1, class _InIt2, class _Pr>
bool lexicographical_compare(_InIt1 _First1, _InIt1 _Last1, _InIt2 _First2,
                             _InIt2 _Last2, _Pr _Pred) {
  for (
      ; _First1 != _Last1 && _First2 != _Last2;
      ++_First1,
      ++_First2) {  //任何一个序列到达尾部，就结束。否则两序列就相对应一一进行对比
    if (_Pred(*_First1, *_First2)) return true;
    if (_Pred(*_First2, *_First1)) return false;
  }
  return _First1 == _Last1 &&
         _First2 != _Last2; /*第一序列到达尾部而第二序列尚有余额*/
}
}  // namespace TinySTL
#endif  // !ALGOBASE_H
