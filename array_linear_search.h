#pragma once

#include <cstddef>
#include <span>

#include "search_result.h"

namespace frank::algo {

enum class search_option { EXACT, NEAREST, NEAREST_DONT_EXIST };

enum class search_direction { FORWARD, BACKWARD };

template <std::size_t SIZE>
search_result
array_linear_search(std::span<int, SIZE> const sorted_array, int value_to_find,
                    std::size_t start_index = 0,
                    search_option nearest = search_option::EXACT,
                    search_direction direction = search_direction::FORWARD,
                    std::size_t max_steps = SIZE) {
  std::size_t search_steps{};
  int last_value{};
  std::size_t step = direction == search_direction::FORWARD ? 1 : -1;
  for (std::size_t i = start_index;
       i >= 0 && i < SIZE && search_steps <= max_steps; i += step) {
    ++search_steps;
    auto value = sorted_array[i];
    if (value > value_to_find) {
      if (nearest == search_option::NEAREST && i > 0) {
        search_result last_value_found{};
        last_value_found.array_index = i - 1;
        last_value_found.has_result = true;
        last_value_found.search_steps = search_steps;
        last_value_found.value = last_value;
        return last_value_found;
      }

      search_result no_value_found{};
      no_value_found.array_index = i;
      no_value_found.search_steps = search_steps;
      no_value_found.value = value;
      return no_value_found;
    }

    if (value == value_to_find) {
      if (nearest == search_option::NEAREST_DONT_EXIST) {
        auto dont_exist = value + 1;
        auto has_value = false;
        for (std::size_t j = i + 1; j < SIZE; ++j) {
          ++search_steps;
          auto next_value = sorted_array[j];
          if (dont_exist == next_value) {
            ++dont_exist;
            continue;
          }

          has_value = true;
          break;
        }

        search_result dont_exist_found{};
        dont_exist_found.array_index = i;
        dont_exist_found.search_steps = search_steps;
        dont_exist_found.value = dont_exist;
        return dont_exist_found;
      }

      search_result value_found{};
      value_found.array_index = i;
      value_found.has_result = true;
      value_found.search_steps = search_steps;
      value_found.value = value;
      return value_found;
    }

    last_value = value;
  }

  search_result no_value_found{};
  no_value_found.array_index = SIZE;
  no_value_found.search_steps = search_steps;
  no_value_found.value = last_value;
  return no_value_found;
}

} // namespace frank::algo
