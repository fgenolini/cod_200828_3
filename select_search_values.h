#pragma once

#include <cstddef>
#include <iostream>
#include <span>

#include "array_linear_search.h"

namespace frank::algo {

template <std::size_t SIZE>
void select_search_values(std::span<int, SIZE> sorted_data, int &value_to_find,
                          int &dont_exist_value_to_find) {
  constexpr auto SEARCH_VALUE = 7982431;

  auto min_data = sorted_data[0];
  auto max_data = sorted_data[sorted_data.size() - 1];
  std::cerr << "Min random element: " << min_data << '\n';
  std::cerr << "Max random element: " << max_data << '\n';

  value_to_find = ((max_data - min_data) / 2) + SEARCH_VALUE;
  std::cerr << "Value to find: " << value_to_find << '\n';
  constexpr auto NEAREST = search_option::NEAREST;
  auto nearest_results_linear =
      array_linear_search_2(sorted_data, value_to_find, 0, NEAREST);
  if (nearest_results_linear.has_result) {
    value_to_find = nearest_results_linear.value;
    std::cerr << "Value to find (exists): " << value_to_find << '\n';
  }

  constexpr auto NEAREST_DONT_EXIST = search_option::NEAREST_DONT_EXIST;
  auto nearest_dont_exist =
      array_linear_search_2(sorted_data, value_to_find, 0, NEAREST_DONT_EXIST);
  dont_exist_value_to_find = nearest_dont_exist.value;
  std::cerr << "Value to find (does not exist): " << dont_exist_value_to_find
            << '\n';
}

} // namespace frank::algo
