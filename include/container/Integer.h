#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>

namespace TinySTL {
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1000

class Integer {
 public:
  Integer();
  Integer(const int &);

  //拷贝构造函数
  // 1,用一个对象初始化另一个对象,Integer A(B);
  // 2,创建对象时赋值,Integer A = B;
  // 3,函数参数
  // 4,函数返回类型为Integer时[局部对象在函数返回时会被析构,相当于在函数外面拿一个对象来接收函数内部的对象]
  Integer(const Integer &);
  Integer(Integer &&);
  ~Integer();
  Integer &operator=(const Integer &);

  Integer abs() const;

  Integer operator-() const;
  Integer &operator++();  // ++i
  Integer &operator--();
  Integer operator++(int);  // i++
  Integer operator--(int);

  Integer operator+(const Integer &) const;
  Integer operator-(const Integer &) const;
  Integer operator*(const Integer &) const;
  Integer operator/(const Integer &) const;
  Integer operator%(const Integer &) const;

  Integer operator+=(const Integer &);
  Integer operator-=(const Integer &);
  Integer operator*=(const Integer &);
  Integer operator/=(const Integer &);
  Integer operator%=(const Integer &);

  bool operator==(const Integer &) const;
  bool operator!=(const Integer &) const;
  bool operator>(const Integer &) const;
  bool operator<(const Integer &) const;
  bool operator>=(const Integer &) const;
  bool operator<=(const Integer &) const;

  friend Integer operator+(const int &, const Integer &);
  friend Integer operator-(const int &, const Integer &);
  friend Integer operator*(const int &, const Integer &);
  friend Integer operator/(const int &, const Integer &);
  friend Integer operator%(const int &, const Integer &);

  friend Integer operator+=(const int &, const Integer &);
  friend Integer operator-=(const int &, const Integer &);
  friend Integer operator*=(const int &, const Integer &);
  friend Integer operator/=(const int &, const Integer &);
  friend Integer operator%=(const int &, const Integer &);

  friend bool operator==(const int &, const Integer &);
  friend bool operator!=(const int &, const Integer &);
  friend bool operator>(const int &, const Integer &);
  friend bool operator<(const int &, const Integer &);
  friend bool operator>=(const int &, const Integer &);
  friend bool operator<=(const int &, const Integer &);

  friend std::ostream &operator<<(std::ostream &, const Integer &);

 private:
  void appendDigit(const char &digit);
  void prependDigit(const char &digit);
  void resize(const int &new_length);
  void trim();

  static int compare_magnitudes(const Integer &A, const Integer &B);
  static Integer add_magnitudes(const Integer &A, const Integer &B);
  static Integer subtract_magnitudes(const Integer &A, const Integer &B);

 private:
  char sign;
  int length;
  char *magnitude;
};

std::ostream &operator<<(std::ostream &out, const Integer &d) {
  if (d.length == 0)
    out << "Not Initialized";
  else {
    if (d.sign == '-') out << '-';
    for (int i = 0; i < d.length; i++) out << d.magnitude[i];
  }
  return out;
}

Integer::Integer() {
  this->sign = '+';
  this->length = 0;
  this->magnitude = nullptr;
}

Integer::~Integer() {
  this->length = 0;
  this->sign = '+';
  if (this->magnitude != nullptr) {
    delete[] this->magnitude;
    this->magnitude = nullptr;
  }
}

Integer::Integer(const int &val) {
  char *new_buffer = new char[MAX_LENGTH];
  if (val >= 0) {
    this->sign = '+';
    sprintf(new_buffer, "%d", val);
    this->magnitude = new_buffer;
    this->length = strlen(this->magnitude);
  } else {
    this->sign = '-';
    sprintf(new_buffer, "%d", -val);
    this->magnitude = new_buffer;
    this->length = strlen(this->magnitude);
  }
}

Integer::Integer(const Integer &rhs) {
  // deep copy
  this->magnitude = nullptr;
  this->sign = '+';
  this->length = 0;
  if (rhs.magnitude != nullptr) {
    this->magnitude = new char[MAX_LENGTH];
    strcpy(this->magnitude, rhs.magnitude);
    this->length = rhs.length;
    this->sign = rhs.sign;
  }
}

Integer::Integer(Integer &&rhs) {
  this->sign = rhs.sign;
  this->length = rhs.length;
  this->magnitude = rhs.magnitude;
  rhs.magnitude = nullptr;
  rhs.sign = '+';
  rhs.length = 0;
}

Integer &Integer::operator=(const Integer &rhs) {
  // deep copy
  if (this != &rhs) {
    if (this->magnitude != nullptr) {
      delete[] this->magnitude;
      this->magnitude = nullptr;
      this->sign = '+';
      this->length = 0;
    }
    if (rhs.magnitude != nullptr) {
      this->magnitude = new char[MAX_LENGTH];
      strcpy(this->magnitude, rhs.magnitude);
      this->length = rhs.length;
      this->sign = rhs.sign;
    }
  }
  return *this;  //不会调用拷贝构造
}

// Integer n1;
// cout<<n1.abs();
// 上面这个n1.abs()其实代表一个临时对象
Integer Integer::abs() const {
  Integer temp = *this;  //赋值形式初始化对象,调用拷贝构造
  temp.sign = '+';
  return temp;  //如果定义了移动构造,就会调用移动构造函数
}

void Integer::appendDigit(const char &digit) {
  this->magnitude[this->length] = digit;
  this->magnitude[this->length + 1] = '\0';
  this->length += 1;
}

void Integer::prependDigit(const char &digit) {
  int idx = this->length;
  this->magnitude[idx + 1] = '\0';
  for (; idx >= 1; idx--) {
    this->magnitude[idx] = this->magnitude[idx - 1];
  }
  this->magnitude[0] = digit;

  this->length += 1;
}

void Integer::resize(const int &new_length) {
  if (new_length < this->length) {
    // do nothing
  } else {
    int zero_num = new_length - this->length;
    while (zero_num--) {
      this->prependDigit('0');
    }
  }
  this->length = new_length;
}

void Integer::trim() {
  // If the calling object contains all '0' digits,then it must assign the
  // calling object an integer value zero
  bool all_zero_flag = true;
  int idx = 0;  //第一个非0数的位置
  int old_length = this->length;
  for (int i = 0; i < old_length; i++) {
    if (this->magnitude[i] == '0') {
      continue;
    } else {
      idx = i;
      all_zero_flag = false;
      break;
    }
  }

  int new_length = old_length - idx;

  if (all_zero_flag) {
    this->magnitude[0] = '0';
    this->magnitude[1] = '\0';
  } else {
    for (int i = 0; idx < old_length; i++, idx++) {
      this->magnitude[i] = this->magnitude[idx];
    }
    this->magnitude[new_length] = '\0';
  }

  this->length = new_length;
}

// A>B :return 1
// A=B :return 0
// A<B :return -1
int Integer::compare_magnitudes(const Integer &A, const Integer &B) {
  // compare length firstly
  if (A.length > B.length) {
    return 1;
  } else if (A.length < B.length) {
    return -1;
  }

  // A.length=B.length
  for (int i = 0; i <= A.length; i++) {
    if (A.magnitude[i] == B.magnitude[i]) {
      if (i == A.length) {
        return 0;
      }
      continue;
    } else {
      if (A.magnitude[i] > B.magnitude[i]) {
        return 1;
      }
      if (A.magnitude[i] < B.magnitude[i]) {
        return -1;
      }
    }
  }
}

Integer Integer::add_magnitudes(const Integer &A, const Integer &B) {
  // their values without considering their sign
  Integer temp(0);
  int a[MAX_LENGTH] = {0};
  int b[MAX_LENGTH] = {0};
  for (int i = strlen(A.magnitude) - 1, j = 0; i >= 0; i--) {
    a[j++] = A.magnitude[i] - '0';
  }
  for (int i = strlen(B.magnitude) - 1, j = 0; i >= 0; i--) {
    b[j++] = B.magnitude[i] - '0';
  }
  for (int i = 0; i < MAX_LENGTH; i++) {
    a[i] += b[i];
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] %= 10;
    }
  }

  for (int i = MAX_LENGTH - 1; i >= 0; i--) {
    if (a[i] == 0) {
      continue;
    } else {
      for (int j = 0; i >= 0; j++, i--) {
        temp.magnitude[j] = a[i] + '0';
        if (i == 0) {
          temp.magnitude[j + 1] = '\0';
          temp.length = j + 1;
          temp.sign = '+';
        }
      }
      break;
    }
  }
  return temp;
}

Integer Integer::subtract_magnitudes(const Integer &A, const Integer &B) {
  // their values without considering their, sign A must greater than B
  if (Integer::compare_magnitudes(A, B) == 1) {
    Integer temp(0);
    int a[MAX_LENGTH] = {0};
    int b[MAX_LENGTH] = {0};
    for (int i = strlen(A.magnitude) - 1, j = 0; i >= 0; i--) {
      a[j++] = A.magnitude[i] - '0';
    }
    for (int i = strlen(B.magnitude) - 1, j = 0; i >= 0; i--) {
      b[j++] = B.magnitude[i] - '0';
    }

    for (int i = 0; i < A.length; i++) {
      a[i] -= b[i];
      while (a[i] < 0) {
        a[i] += 10;
        a[i + 1]--;
      }
    }

    for (int i = MAX_LENGTH - 1; i >= 0; i--) {
      if (a[i] == 0) {
        continue;
      } else {
        for (int j = 0; i >= 0; j++, i--) {
          temp.magnitude[j] = a[i] + '0';
          if (i == 0) {
            temp.magnitude[j + 1] = '\0';
            temp.length = j + 1;
          }
        }
        break;
      }
    }
    temp.trim();
    return temp;
  }
}

Integer Integer::operator-() const {
  Integer temp = *this;
  if (temp.sign == '-') {
    temp.sign = '+';
  } else if (temp.sign == '+') {
    temp.sign = '-';
  }
  return temp;
}
Integer &Integer::operator++() {
  Integer val_1(1);
  if (this->sign == '-') {
    *this = Integer::subtract_magnitudes(*this, val_1);
    this->sign = '-';
  } else if (this->sign == '+') {
    *this = Integer::add_magnitudes(*this, val_1);
    this->sign = '+';
  }
  return *this;
}
Integer &Integer::operator--() {
  Integer val_1(1);
  if (this->sign == '+') {
    *this = Integer::subtract_magnitudes(*this, val_1);
    this->sign = '+';
  } else if (this->sign == '-') {
    *this = Integer::add_magnitudes(*this, val_1);
    this->sign = '-';
  }
  return *this;
}
Integer Integer::operator++(int) {
  Integer temp = *this;
  this->operator++();
  return temp;
}
Integer Integer::operator--(int) {
  Integer temp = *this;
  this->operator--();
  return temp;
}
Integer Integer::operator+(const Integer &rhs) const {
  Integer temp;
  if (this->sign == '-') {
    temp = Integer::subtract_magnitudes(*this, rhs);
    temp.sign = '-';
  } else if (this->sign == '+') {
    temp = Integer::add_magnitudes(*this, rhs);
    temp.sign = '+';
  }
  return temp;
}

// A-B, we should consider their sign and size
// (+)A-(+)B: |(>: A-B,sign='+')|(=:0)|(<:B-A,sign='-')
// (+)A-(-)B: |(>、=、<:A+B,sign='+')
// (-)A-(+)B: |(>、=、<:A+B,sign='-')
// (-)A-(-)B: |(>: A-B,sign='-')|(=:0)|(<:B-A,sign='+')
// Integer Integer::operator-(const Integer &rhs) const {
//  // todo
//}
// Integer Integer::operator*(const Integer &rhs) const {
//  // todo
//}
// Integer Integer::operator/(const Integer &rhs) const {
//  // todo
//}
// Integer Integer::operator%(const Integer &rhs) const {
//  // todo
//}
//
// Integer Integer::operator+=(const Integer &rhs) {
//  // todo
//}
// Integer Integer::operator-=(const Integer &rhs) {
//  // todo
//}
// Integer Integer::operator*=(const Integer &rhs) {
//  // todo
//}
// Integer Integer::operator/=(const Integer &rhs) {
//  // todo
//}
// Integer Integer::operator%=(const Integer &rhs) {
//  // todo
//}

bool Integer::operator==(const Integer &rhs) const {
  if (this->sign != rhs.sign) {
    return false;
  } else {
    int res = Integer::compare_magnitudes(*this, rhs);
    if (res == 0) {
      return true;
    } else {
      return false;
    }
  }
}
bool Integer::operator!=(const Integer &rhs) const { return !(*this == rhs); }
bool Integer::operator>(const Integer &rhs) const {
  if (this->sign < rhs.sign) {  // compare ASCII '-':45,'+':43
    return true;
  } else if (this->sign == rhs.sign) {
    // if both of them have the same sign,you need to consider the positive and
    // negative
    int res = Integer::compare_magnitudes(*this, rhs);
    if (this->sign == '+') {
      if (res == 0) return false;
      if (res == 1) return true;
      if (res == -1) return false;
    }
    if (this->sign == '-') {
      if (res == 0) return false;
      if (res == 1) return false;
      if (res == -1) return true;
    }
  } else {
    return false;
  }
}
bool Integer::operator<(const Integer &rhs) const { return !(*this > rhs); }
bool Integer::operator>=(const Integer &rhs) const { return !(*this < rhs); }
bool Integer::operator<=(const Integer &rhs) const { return !(*this > rhs); }

// Integer operator+(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator-(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator*(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator/(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator%(const int &val, const Integer &rhs) {
//  // todo
//}
//
// Integer operator+=(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator-=(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator*=(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator/=(const int &val, const Integer &rhs) {
//  // todo
//}
// Integer operator%=(const int &val, const Integer &rhs) {
//  // todo
//}

bool operator==(const int &val, const Integer &rhs) {
  Integer temp(val);
  return temp == rhs;
}
bool operator!=(const int &val, const Integer &rhs) {
  Integer temp(val);
  return temp != rhs;
}
bool operator>(const int &val, const Integer &rhs) {
  Integer temp(val);
  return temp > rhs;
}
bool operator<(const int &val, const Integer &rhs) {
  Integer temp(val);
  return !(temp > rhs);
}
bool operator>=(const int &val, const Integer &rhs) {
  Integer temp(val);
  return temp >= rhs;
}
bool operator<=(const int &val, const Integer &rhs) {
  Integer temp(val);
  return temp <= rhs;
}
}  // namespace TinySTL

#endif  // INTEGER_H