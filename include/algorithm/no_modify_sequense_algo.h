#ifndef NO_MODIFY_SEQUENSE_ALGO_H
#define NO_MODIFY_SEQUENSE_ALGO_H

#include "fundation/iterator.h"
#include "fundation/type_traits.h"
#include "fundation/utility.h"

namespace TinySTL {
/**
 *  @brief  Checks that a predicate is true for all the elements
 *          of a sequence.
 *  @param  first   An input iterator.
 *  @param  last    An input iterator.
 *  @param  p       A predicate.
 *  @return  True if the check is true, false otherwise.
 *
 *  Returns true if @p p is true for each element in the range
 *  @p [first,last), and false otherwise.
 */
template <typename InputIt, typename UnaryPredicate>
inline bool all_of(InputIt first, InputIt last, UnaryPredicate p) {
  // return last == TinySTL::find_if_not(first, last, p);
  while (first != last) {
    if (p(*first)) {
      first++;
      continue;
    }
    return false;
  }
  return true;
}

/**
 *  @brief  Checks that a predicate is false for at least an element
 *          of a sequence.
 *  @param  first   An input iterator.
 *  @param  last    An input iterator.
 *  @param  p       A predicate.
 *  @return  True if the check is true, false otherwise.
 *
 *  Returns true if an element exists in the range @p [first,last)
 *  such that @p p is true, and false otherwise.
 */
template <typename InputIt, typename UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate p) {
  // return !TinySTL::none_of(first, last, p);
  while (first != last) {
    if (p(*first)) {
      return true;
    }
    first++;
  }
  return false;
}

/**
 *  @brief  Checks that a predicate is false for all the elements
 *          of a sequence.
 *  @param  first   An input iterator.
 *  @param  last    An input iterator.
 *  @param  p       A predicate.
 *  @return  True if the check is true, false otherwise.
 *
 *  Returns true if @p p is false for each element in the range
 *  @p [first,last), and false otherwise.
 */
template <typename InputIt, typename UnaryPredicate>
bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
  // return last == TinySTL::find_if(first, last, p);
  while (first != last) {
    if (p(*first)) {
      return false;
    }
    first++;
  }
  return true;
}

/**
 *  @brief Apply a function to every element of a sequence.
 *  @ingroup non_mutating_algorithms
 *  @param  first  An input iterator.
 *  @param  last   An input iterator.
 *  @param  f      A unary function object.
 *  @return   @p f
 *
 *  Applies the function object @p f to each element in the range
 *  @p [first,last).  @p f must not modify the order of the sequence.
 *  If @p f has a return value it is ignored.
 */
template <typename InputIt, typename UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
  while (first != last) {
    f(*first);
    first++;
  }
  return f;
}

/**
 *  @brief Count the number of copies of a value in a sequence.
 *  @param  first  An input iterator.
 *  @param  last   An input iterator.
 *  @param  value  The value to be counted.
 *  @return   The number of iterators @c i in the range @p [first,last)
 *  for which @c *i == @p value
 */
template <typename InputIt, typename T>
typename TinySTL::iterator_traits<InputIt>::difference_type count(
    InputIt first, InputIt last, const T& value) {
  typename TinySTL::iterator_traits<InputIt>::difference_type n = 0;
  for (; first != last; first++) {
    if (*first == value) {
      n++;
    }
  }
  return n;
}

/**
 *  @brief Count the elements of a sequence for which a predicate is true.
 *  @ingroup non_mutating_algorithms
 *  @param  first  An input iterator.
 *  @param  last   An input iterator.
 *  @param  p      A predicate.
 *  @return   The number of iterators @c i in the range @p [first,last)
 *  for which @p p(*i) is true.
 */
template <typename InputIt, typename UnaryPredicate>
typename TinySTL::iterator_traits<InputIt>::difference_type count_if(
    InputIt first, InputIt last, UnaryPredicate p) {
  typename TinySTL::iterator_traits<InputIt>::difference_type n = 0;
  for (; first != last; first++) {
    if (p(*first)) {
      n++;
    }
  }
  return n;
}

/**
 *  @brief Finds the places in ranges which don't match.
 *  @ingroup non_mutating_algorithms
 *  @param first1  An input iterator.
 *  @param last1   An input iterator.
 *  @param first2  An input iterator.
 *  @return A pair of iterators pointing to the first mismatch.
 *
 *  This compares the elements of two ranges using @c == and returns a pair
 *  of iterators.  The first iterator points into the first range, the
 *  second iterator points into the second range, and the elements pointed
 *  to by the iterators are not equal.
 */
template <typename InputIt1, typename InputIt2>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    first1++;
    first2++;
  }
  return TinySTL::pair<InputIt1, InputIt2>(first1, first2);
}

/**
 *  @brief Finds the places in ranges which don't match.
 *  @ingroup non_mutating_algorithms
 *  @param  irst1   An input iterator.
 *  @param  last1   An input iterator.
 *  @param  first2  An input iterator.
 *  @param  p       A binary predicate
 *  @return   A pair of iterators pointing to the first mismatch.
 *
 *  This compares the elements of two ranges using the binary_pred
 *  parameter, and returns a pair of iterators.  The first iterator points into
 *  the first range, the second iterator points into the second range, and the
 *  elements pointed to by the iterators are not equal.
 */
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2, BinaryPredicate p) {
  while (first1 != last1 && p(*first1, *first2)) {
    first1++;
    first2++;
  }
  return TinySTL::pair<InputIt1, InputIt2>(first1, first2);
}

/**
 *  @brief Finds the places in ranges which don't match.
 *  @ingroup non_mutating_algorithms
 *  @param  first1  An input iterator.
 *  @param  last1   An input iterator.
 *  @param  first2  An input iterator.
 *  @param  last2   An input iterator.
 *  @return  A pair of iterators pointing to the first mismatch.
 *
 *  This compares the elements of two ranges using @c == and returns a pair
 *  of iterators.  The first iterator points into the first range, the
 *  second iterator points into the second range, and the elements pointed
 *  to by the iterators are not equal.
 */
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2, InputIt2 last2) {
  while (first1 != last1 && first2 != last2 && *first1 == *first2) {
    first1++;
    first2++;
  }
  return TinySTL::pair<InputIt1, InputIt2>(first1, first2);
}

/**
 *  @brief Finds the places in ranges which don't match.
 *  @ingroup non_mutating_algorithms
 *  @param  first1  An input iterator.
 *  @param  last1   An input iterator.
 *  @param  first2  An input iterator.
 *  @param  last2   An input iterator.
 *  @param  p   A binary predicate
 *  @return   A pair of iterators pointing to the first mismatch.
 *
 *  This compares the elements of two ranges using the binary_pred
 *  parameter, and returns a pair
 *  of iterators.  The first iterator points into the first range, the
 *  second iterator points into the second range, and the elements pointed
 *  to by the iterators are not equal.
 */
template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
TinySTL::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                           InputIt2 first2, InputIt2 last2,
                                           BinaryPredicate p) {
  while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
    first1++;
    first2++;
  }
  return TinySTL::pair<InputIt1, InputIt2>(first1, first2);
}

/**
 *  @brief Finds the first position in which
 *  @ingroup non_mutating_algorithms
 *  @param  first1  An input iterator.
 *  @param  last1   An input iterator.
 *  @param  first2  An input iterator.
 *
 *  This compares the elements of two ranges using the binary_pred
 *  parameter, and returns a pair
 *  of iterators.  The first iterator points into the first range, the
 *  second iterator points into the second range, and the elements pointed
 *  to by the iterators are not equal.
 */
template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T& value) {
  // todo
}

template <typename InputIt, typename UnaryPredicate>
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p) {
  // todo
}

template <typename InputIt, typename UnaryPredicate>
InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q) {
  // todo
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                    ForwardIt2 s_last) {
  // todo
}

template <typename ForwardIt1, typename ForwardIt2, typename BinaryPredicate>
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                    ForwardIt2 s_last, BinaryPredicate p) {
  // todo
}

template <typename ForwardIt1, typename ForwardIt2>
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                         ForwardIt2 s_last) {
  // todo
}
}  // namespace TinySTL
#endif
