// Binary search operations (on sorted ranges)
// 1,lower_bound:	returns an iterator to the first element not less than
// the given value 2,upper_bound: returns an iterator to the first element
// greater than a certain value 3,binary_serach: determines if an element exists
// in a certain range 4,equal_range: return range of elements matching a
// specific key
#ifndef BINARY_SERACH_ALGO_H
#define BINARY_SERACH_ALGO_H

#include "fundation/utility.h"
namespace TinySTL {
template <class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value) {
  // todo
}

template <class ForwardIt, class T, class Compare>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value,
                      Compare comp) {
  // todo
}

template <class ForwardIt, class T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value) {
  // todo
}

template <class ForwardIt, class T, class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value,
                      Compare comp) {
  // todo
}

template <class ForwardIt, class T>
bool binary_search(ForwardIt first, ForwardIt last, const T& value) {
  // todo
}

template <class ForwardIt, class T, class Compare>
bool binary_search(ForwardIt first, ForwardIt last, const T& value,
                   Compare comp) {
  // todo
}

template <class ForwardIt, class T>
TinySTL::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                                const T& value) {
  // todo
}

template <class ForwardIt, class T, class Compare>
TinySTL::pair<ForwardIt, ForwardIt> equal_range(ForwardIt first, ForwardIt last,
                                                const T& value, Compare comp) {
  // todo
}
}  // namespace TinySTL
#endif
