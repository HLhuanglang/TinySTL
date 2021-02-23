#include <iostream>

#include "container/Integer.h"

void Integer_test() {
  // Test constructors
  TinySTL::Integer n1;
  TinySTL::Integer n2(-10023000);
  TinySTL::Integer n3(n2);
  TinySTL::Integer n4 = n2;
  std::cout << "Default Integer object n1 is " << n1 << std::endl;
  std::cout << "Non-default Integer object n2 is " << n2 << std::endl;
  std::cout << "Non-default Integer object n3 is " << n3 << std::endl;
  std::cout << "Non-default Integer object n3 is " << n4 << std::endl;

  // Test destructor
  n2.~Integer();
  std::cout << "After destructing it, n2 is now " << n2 << std::endl;

  // Test assignment operators
  n1 = n3;
  std::cout << "After assigning n1 the value of n3, n1 is now " << n1
            << std::endl;
  n2 = 8;
  std::cout << "After assigning n2 the integer value 8, n2 is now " << n2
            << std::endl;

  // Test absolute value
  std::cout << "The absolute value of n1 is " << n1.abs() << std::endl;
  std::cout << "The absolute value of n2 is " << n2.abs() << std::endl;
  std::cout << "The absolute value of n3 is " << n3.abs() << std::endl;

  // Test arithmetic operations with relatively small values in order to
  // validate the correctness of our program
  int x, y, z;
  TinySTL::Integer d1, d2, d3, d4;
  bool success = true;
  srand(time(0));  // Comment this line of code to get same random numbers on
                   // repeated runs of the program
  for (int i = 0; i < 25; i++) {
    std::cout << "========================================================"
              << std::endl;
    // Test equality comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x == y ? std::cout << x << " == " << y << std::endl
           : std::cout << x << " is not == " << y << std::endl;
    d1 == d2 ? std::cout << d1 << " == " << d2 << std::endl
             : std::cout << d1 << " is not == " << d2 << std::endl;
    x == d2 ? std::cout << x << " == " << d2 << std::endl
            : std::cout << x << " is not == " << d2 << std::endl;
    if (((x == y) == (d1 == d2)) && ((x == y) == (x == d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test not equality comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x != y ? std::cout << x << " != " << y << std::endl
           : std::cout << x << " is not != " << y << std::endl;
    d1 != d2 ? std::cout << d1 << " != " << d2 << std::endl
             : std::cout << d1 << " is not != " << d2 << std::endl;
    x != d2 ? std::cout << x << " != " << d2 << std::endl
            : std::cout << x << " is not != " << d2 << std::endl;
    if (((x != y) == (d1 != d2)) && ((x != y) == (x != d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test greater than comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x > y ? std::cout << x << " > " << y << std::endl
          : std::cout << x << " is not > " << y << std::endl;
    d1 > d2 ? std::cout << d1 << " > " << d2 << std::endl
            : std::cout << d1 << " is not > " << d2 << std::endl;
    x > d2 ? std::cout << x << " > " << d2 << std::endl
           : std::cout << x << " is not > " << d2 << std::endl;
    if (((x > y) == (d1 > d2)) && ((x > y) == (x > d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test less than comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x < y ? std::cout << x << " < " << y << std::endl
          : std::cout << x << " is not < " << y << std::endl;
    d1 < d2 ? std::cout << d1 << " < " << d2 << std::endl
            : std::cout << d1 << " is not < " << d2 << std::endl;
    x < d2 ? std::cout << x << " < " << d2 << std::endl
           : std::cout << x << " is not < " << d2 << std::endl;
    if (((x < y) == (d1 < d2)) && ((x < y) == (x < d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test greater than or equal comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x >= y ? std::cout << x << " >= " << y << std::endl
           : std::cout << x << " is not >= " << y << std::endl;
    d1 >= d2 ? std::cout << d1 << " >= " << d2 << std::endl
             : std::cout << d1 << " is not >= " << d2 << std::endl;
    x >= d2 ? std::cout << x << " >= " << d2 << std::endl
            : std::cout << x << " is not >= " << d2 << std::endl;
    if (((x >= y) == (d1 >= d2)) && ((x >= y) == (x >= d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test less than or equal comparison
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    y = rand() % 2 ? rand() : -rand();
    d2 = y;
    x <= y ? std::cout << x << " <= " << y << std::endl
           : std::cout << x << " is not <= " << y << std::endl;
    d1 <= d2 ? std::cout << d1 << " <= " << d2 << std::endl
             : std::cout << d1 << " is not <= " << d2 << std::endl;
    x <= d2 ? std::cout << x << " <= " << d2 << std::endl
            : std::cout << x << " is not <= " << d2 << std::endl;
    if (((x <= y) == (d1 <= d2)) && ((x <= y) == (x <= d2)))
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test arithmetic negation operation
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    std::cout << "x = " << x << " and -x is " << -x << std::endl;
    std::cout << "d1 = " << d1 << " and -d1 is " << -d1 << std::endl;
    if (-d1 == -x)
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test pre-increment operation
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    std::cout << "x = " << x << " and ";
    std::cout << "++x is " << ++x << std::endl;
    std::cout << "d1 = " << d1 << " and ";
    std::cout << "++d1 is " << ++d1 << std::endl;
    if (d1 == x)
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test pre-decrement operation
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    std::cout << "x = " << x << " and ";
    std::cout << "--x is " << --x << std::endl;
    std::cout << "d1 = " << d1 << " and ";
    std::cout << "--d1 is " << --d1 << std::endl;
    if (d1 == x)
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test post-increment operation
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    std::cout << "x = " << x << " and ";
    x++;
    std::cout << "x++ is " << x << std::endl;
    std::cout << "d1 = " << d1 << " and ";
    d1++;
    std::cout << "d1++ is " << d1 << std::endl;
    if (d1 == x)
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;

    // Test post-decrement operation
    x = rand() % 2 ? rand() : -rand();
    d1 = x;
    std::cout << "x = " << x << " and ";
    x--;
    std::cout << "x-- is " << x << std::endl;
    std::cout << "d1 = " << d1 << " and ";
    d1--;
    std::cout << "d1-- is " << d1 << std::endl;
    if (d1 == x)
      std::cout << "Correct computation." << std::endl;
    else {
      std::cout << "Wrong computation. Something went wrong. Check your work."
                << std::endl;
      success = false;
      break;
    }
    std::cout << std::endl;
  }
}
