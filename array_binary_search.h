#pragma once

#include <cstddef>
#include <span>

#include "array_linear_search.h"
#include "search_result.h"

namespace frank::algo {

// Search 2nd quarter, and then 1st quarter
template <std::size_t SIZE>
search_result left_search(std::span<array_value, SIZE> const sorted_array,
                          array_value value_to_find, array_index middle,
                          std::size_t width) {
  auto second_quarter = array_linear_search_2(
      sorted_array, value_to_find, middle, search_option::EXACT,
      search_direction::BACKWARD, width);
  if (second_quarter.has_result || second_quarter.value < value_to_find)
    return second_quarter;

  auto first_quarter_steps = second_quarter.search_steps;
  auto beginning = 0ULL;
  auto first_quarter = array_linear_search_2(sorted_array, value_to_find,
                                             beginning, search_option::EXACT,
                                             search_direction::FORWARD, width);
  first_quarter.search_steps += first_quarter_steps;
  return first_quarter;
}

// Search 3rd quarter, and then 4th quarter
template <std::size_t SIZE>
search_result right_search(std::span<array_value, SIZE> const sorted_array,
                           array_value value_to_find, array_index middle,
                           std::size_t width) {
  auto third_quarter = array_linear_search_2(sorted_array, value_to_find,
                                             middle, search_option::EXACT,
                                             search_direction::FORWARD, width);
  if (third_quarter.has_result || third_quarter.value > value_to_find)
    return third_quarter;

  auto third_quarter_steps = third_quarter.search_steps;
  auto end = sorted_array.size() - 1;
  auto fourth_quarter = array_linear_search_2(
      sorted_array, value_to_find, end, search_option::EXACT,
      search_direction::BACKWARD, width);
  fourth_quarter.search_steps += third_quarter_steps;
  return fourth_quarter;
}

// Rudimentary improvement over linear search
// by simple double "divide and conquer" / two step dichotomy (4 quarters)
template <std::size_t SIZE>
search_result
array_binary_search(std::span<array_value, SIZE> const sorted_array,
                    array_value value_to_find,
                    std::map<array_value, array_index> const &bins) {
  constexpr auto NO_BINARY_SEARCH = 17;
  if (SIZE < 1)
    return search_result{};

  if (SIZE < NO_BINARY_SEARCH)
    return array_linear_search(sorted_array, value_to_find, bins);

  if (bins.count(value_to_find)) {
    auto index = bins.at(value_to_find);
    search_result value_in_bins{};
    value_in_bins.index = index;
    value_in_bins.has_result = true;
    value_in_bins.search_steps = 1;
    value_in_bins.value = value_to_find;
    return value_in_bins;
  }

  for (auto i = 0ULL; i < bins.size() - 1; ++i) {
    auto start = bin_start[i];
    auto next_start = bin_start[i + 1];
    if (value_to_find < start || value_to_find > next_start)
      continue;

    auto end_index = bins.at(next_start);
    auto start_index = bins.at(start);
    auto half_index_width = (end_index - start_index) / 2;
    auto middle = start_index + half_index_width;
    auto middle_value = sorted_array[middle];
    if (value_to_find <= middle_value)
      return left_search(sorted_array, value_to_find, middle, half_index_width);

    return right_search(sorted_array, value_to_find, middle, half_index_width);
  }

  return search_result{};
}

} // namespace frank::algo
