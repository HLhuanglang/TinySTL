#ifndef NO_MODIFY_SEQUENSE_ALGO_H
#define NO_MODIFY_SEQUENSE_ALGO_H

#include "fundation/iterator.h"
#include "fundation/type_traits.h"
#include "fundation/utility.h"

namespace TinySTL {
template <class InputIt, class UnaryPredicate>
bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <class InputIt, class UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <class InputIt, class UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
  // todo
}

template <class InputIt, class T>
typename TinySTL::iterator_traits<InputIt>::difference_type count(
    InputIt first, InputIt last, const T& value) {
  // todo
}

template <class InputIt, class UnaryPredicate>
typename TinySTL::iterator_traits<InputIt>::difference_type count_if(
    InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <class InputIt1, class InputIt2>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2) {
  // todo
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2, BinaryPredicate p) {
  // todo
}

template <class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value) {
  // todo
}

template <class InputIt, class UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <class InputIt, class UnaryPredicate>
InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q) {
  // todo
}

template <class ForwardIt1, class ForwardIt2>
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                    ForwardIt2 s_last) {
  // todo
}

template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                    ForwardIt2 s_last, BinaryPredicate p) {
  // todo
}

template <class ForwardIt1, class ForwardIt2>
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                         ForwardIt2 s_last) {
  // todo
}

template <class InputIt, class ForwardIt>
InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                      ForwardIt s_last) {
  // todo
}

template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                         ForwardIt2 s_last, BinaryPredicate p) {
  // todo
}
template <class InputIt, class ForwardIt, class BinaryPredicate>
InputIt find_first_of(InputIt first, InputIt last, ForwardIt s_first,
                      ForwardIt s_last, BinaryPredicate p) {
  // todo
}
}  // namespace TinySTL
#endif
