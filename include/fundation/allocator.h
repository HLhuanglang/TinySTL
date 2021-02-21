#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <new>

#include "alloc.h"
#include "construct.h"
#include "exceptdef.h"
namespace TinySTL {
template <typename T>
class allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using difference_type = ptrdiff_t;
  using size_type = size_t;
  using const_reference = const T&;
  using const_pointer = const T*;

 public:
  //=================================================================[[内存申请与释放
  static T* allocate();
  static T* allocate(IN size_t _Count);
  static void deallocate(IN T* _Ptr);
  static void deallocate(IN T* _Ptr, IN size_t _Count);
  //=================================================================]]内存申请与释放

  //=================================================================[[对象创建与销毁
  static void construct(IN T* _Ptr);
  static void construct(IN T* _Ptr, IN const T& _Val);
  static void destory(IN T* _Ptr);
  static void destory(IN T* _First, IN T* _Last);
  //=================================================================]]对象创建与销毁
};  // end of class allocator

/******************************************************
函 数 名	：allocate
函数作用	：申请一个对象大小的内存,返回内存的起始地址
函数参数	：无
返 回 值	：返回内存地址指针
******************************************************/
template <typename T>
T* allocator<T>::allocate() { /*申请内存大小为一个对象大小*/
  return static_cast<T*>(TinySTL::alloc::allocate(sizeof(T)));
}

/******************************************************
函 数 名	：allocate
函数作用	：申请_Count个对象大小的内存,返回内存的起始地址
函数参数	：
                [IN]	_Count:申请对象个数
返 回 值	：返回内存地址指针
******************************************************/
template <typename T>
T* allocator<T>::allocate(IN size_t _Count) {
  if (_Count == 0) {
    std::cerr << "申请内存需大于0";
  }
  return static_cast<T*>(TinySTL::alloc::allocate(_Count * sizeof(T)));
}

/******************************************************
函 数 名	：deallocate
函数作用	：释放_Ptr指针指向的内存空间
函数参数	：
                [IN]	_Ptr:指向目标内存起始地址的指针
返 回 值	：无
******************************************************/
template <typename T>
void allocator<T>::deallocate(IN T* _Ptr) {
  TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T));
}

/******************************************************
函 数 名	：deallocate
函数作用	：释放_Ptr指向的_Count个对象大小的内存
函数参数	：
                [IN]	_Ptr:指向目标内存起始地址的指针
                [IN]	_Count:对象个数
返 回 值	：无
******************************************************/
template <typename T>
void allocator<T>::deallocate(IN T* _Ptr, IN size_t _Count) {
  if (_Count == 0) {
    return;
  }
  TinySTL::alloc::deallocate(static_cast<void*>(_Ptr), sizeof(T) * _Count);
}

/******************************************************
函 数 名	：construct
函数作用	：在_Ptr指向的位置构造对象，对象值默认
函数参数	：
                [IN]	_Ptr:指向目标内存起始地址的指针
返 回 值	：无
******************************************************/
template <typename T>
void allocator<T>::construct(IN T* _Ptr) {
  TinySTL::construct(_Ptr);
}

/******************************************************
函 数 名	：construct
函数作用	：在_Ptr指向的位置构造对象，对象值为_Val
函数参数	：
                [IN]	_Ptr:指向目标内存起始地址的指针
                [IN]	_Val:构造对象的值
返 回 值	：无
******************************************************/
template <typename T>
void allocator<T>::construct(IN T* _Ptr, IN const T& _Val) {
  TinySTL::construct(_Ptr, _Val);
}

/******************************************************
函 数 名	：destory
函数作用	：析构_Ptr指向的内存，默认一个对象大小
函数参数	：
                [IN]	_Ptr:指向目标内存起始地址的指针
返 回 值	：无
******************************************************/
template <typename T>
void allocator<T>::destory(IN T* _Ptr) {
  TinySTL::destory(_Ptr);
}

/******************************************************
函 数 名	：destory
函数作用	：析构[_First，_Last)区间内的对象
函数参数	：
                [IN]	_First:目标区间起始地址
                [IN]	_Last :目标区间结束地址
返 回 值	：无
******************************************************/
//析构[_First,_Last]范围内对象
template <typename T>
void allocator<T>::destory(IN T* _First, IN T* _Last) {
  for (; _First != _Last; ++_First) {
    TinySTL::destory(_First);
  }
}
}  // namespace TinySTL
#endif  // !ALLOCATOR_H
