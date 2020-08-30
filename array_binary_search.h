#pragma once

#include <cstddef>
#include <span>

#include "array_linear_search.h"
#include "search_result.h"

namespace frank::algo {

template <std::size_t SIZE>
search_result left_search(std::span<int, SIZE> const sorted_array,
                          int value_to_find, std::size_t middle) {
  auto half_middle = middle / 2;
  auto left_results = array_linear_search_2(
      sorted_array, value_to_find, middle, search_option::EXACT,
      search_direction::BACKWARD, half_middle);
  if (left_results.has_result || left_results.value < value_to_find)
    return left_results;

  auto left_steps = left_results.search_steps;
  auto right_results = array_linear_search_2(
      sorted_array, value_to_find, 0, search_option::EXACT,
      search_direction::FORWARD, half_middle);
  right_results.search_steps += left_steps;
  return right_results;
}

template <std::size_t SIZE>
search_result right_search(std::span<int, SIZE> const sorted_array,
                           int value_to_find, std::size_t middle) {
  auto half_middle = middle / 2;
  auto right_results = array_linear_search_2(
      sorted_array, value_to_find, middle, search_option::EXACT,
      search_direction::FORWARD, half_middle);
  if (right_results.has_result || right_results.value > value_to_find)
    return right_results;

  auto right_steps = right_results.search_steps;
  auto left_results = array_linear_search_2(
      sorted_array, value_to_find, 0, search_option::EXACT,
      search_direction::BACKWARD, half_middle);
  left_results.search_steps += right_steps;
  return left_results;
}

// Rudimentary improvement over linear search
// by simple single "divide and conquer" / two step dichotomy
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
