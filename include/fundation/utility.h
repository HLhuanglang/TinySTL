#ifndef UTILITY_H
#define UTILITY_H
namespace TinySTL {
template <class _Ty1, class _Ty2>
struct pair {
  typedef _Ty1 first_type;
  typedef _Ty2 second_type;

  //成员变量
  first_type first;
  second_type second;

  //构造函数
  pair() : first(_Ty1()), second(_Ty2()) {}

  pair(const _Ty1& _Val1, const _Ty2& _Val2) : first(_Val1), second(_Val2) {}

  template <class _Other1, class _Other2>
  pair(const pair<_Other1, _Other2>& _Right)
      : first(_Right.first), second(_Right.second) {}
  ~pair() = default;
};  // end of class pair

template <class _Ty1, class _Ty2>
pair<_Ty1, _Ty2> make_pair(const _Ty1& _Val1, const _Ty2& _Val2) {
  return pair<_Ty1, _Ty2>(_Val1, _Val2);
}

//==================================================================[[运算符重载
template <class _Ty1, class _Ty2>
bool operator==(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
  return (_Left.first == _Right.first && _Left.second == _Right.second);
}

template <class _Ty1, class _Ty2>
bool operator!=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
  return (!(_Left == _Right));
}

template <class _Ty1, class _Ty2>
bool operator<(
    const pair<_Ty1, _Ty2>& _Left,
    const pair<_Ty1, _Ty2>& _Right) {  //优先比较first，first相等时才比较second
  return (_Left.first < _Right.first ||
          (!(_Right.first < _Left.first) && _Left.second < _Right.second));
}

template <class _Ty1, class _Ty2>
bool operator>(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
  return (_Right < _Left);
}

template <class _Ty1, class _Ty2>
bool operator<=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
  return (!(_Right < _Left));
}

template <class _Ty1, class _Ty2>
bool operator>=(const pair<_Ty1, _Ty2>& _Left, const pair<_Ty1, _Ty2>& _Right) {
  return (!(_Left < _Right));
}
//==================================================================运算符重载]]
}  // namespace TinySTL
#endif  // !UTILITY_H
