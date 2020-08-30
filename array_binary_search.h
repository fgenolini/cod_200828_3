#pragma once

#include <cstddef>
#include <span>

#include "array_linear_search.h"
#include "search_result.h"

namespace frank::algo {

// Search 2nd quarter, and then 1st quarter
template <std::size_t SIZE>
search_result left_search(std::span<int, SIZE> const sorted_array,
                          int value_to_find, std::size_t middle) {
  auto half_middle = middle / 2;
  auto second_quarter = array_linear_search_2(
      sorted_array, value_to_find, middle, search_option::EXACT,
      search_direction::BACKWARD, half_middle);
  if (second_quarter.has_result || second_quarter.value < value_to_find)
    return second_quarter;

  auto first_quarter_steps = second_quarter.search_steps;
  auto beginning = 0ULL;
  auto first_quarter = array_linear_search_2(
      sorted_array, value_to_find, beginning, search_option::EXACT,
      search_direction::FORWARD, half_middle);
  first_quarter.search_steps += first_quarter_steps;
  return first_quarter;
}

// Search 3rd quarter, and then 4th quarter
template <std::size_t SIZE>
search_result right_search(std::span<int, SIZE> const sorted_array,
                           int value_to_find, std::size_t middle) {
  auto half_middle = middle / 2;
  auto third_quarter = array_linear_search_2(
      sorted_array, value_to_find, middle, search_option::EXACT,
      search_direction::FORWARD, half_middle);
  if (third_quarter.has_result || third_quarter.value > value_to_find)
    return third_quarter;

  auto third_quarter_steps = third_quarter.search_steps;
  auto end = sorted_array.size() - 1;
  auto fourth_quarter = array_linear_search_2(
      sorted_array, value_to_find, end, search_option::EXACT,
      search_direction::BACKWARD, half_middle);
  fourth_quarter.search_steps += third_quarter_steps;
  return fourth_quarter;
}

// Rudimentary improvement over linear search
// by simple double "divide and conquer" / two step dichotomy (4 quarters)
template <std::size_t SIZE>
search_result array_binary_search(std::span<int, SIZE> const sorted_array,
                                  int value_to_find) {
  constexpr auto NO_BINARY_SEARCH = 17;
  if (SIZE < 1)
    return search_result{};

  if (SIZE < NO_BINARY_SEARCH)
    return array_linear_search(sorted_array, value_to_find);

  auto middle = sorted_array.size() / 2;
  auto middle_value = sorted_array[middle];
  if (value_to_find <= middle_value)
    return left_search(sorted_array, value_to_find, middle);

  return right_search(sorted_array, value_to_find, middle);
}

} // namespace frank::algo
