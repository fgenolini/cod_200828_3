#pragma once

#include <cstddef>
#include <map>
#include <span>

#include "search_result.h"

namespace frank::algo {

enum class search_option { EXACT, NEAREST, NEAREST_DONT_EXIST };

enum class search_direction { FORWARD, BACKWARD };

template <std::size_t SIZE>
search_result
array_linear_search_2(std::span<array_value, SIZE> const sorted_array,
                      array_value value_to_find, std::size_t start_index = 0,
                      search_option nearest = search_option::EXACT,
                      search_direction direction = search_direction::FORWARD,
                      std::size_t max_steps = SIZE) {
  if (SIZE < 1)
    return search_result{};

  std::size_t search_steps{};
  array_value last_value{};
  std::size_t step = direction == search_direction::FORWARD ? 1 : -1;
  for (array_index i = start_index;
       i >= 0 && i < SIZE && search_steps <= max_steps; i += step) {
    ++search_steps;
    auto value = sorted_array[i];
    if (value > value_to_find) {
      if (nearest == search_option::NEAREST && i > 0) {
        search_result last_value_found{};
        last_value_found.index = i - 1;
        last_value_found.has_result = true;
        last_value_found.search_steps = search_steps;
        last_value_found.value = last_value;
        return last_value_found;
      }

      search_result no_value_found{};
      no_value_found.index = i;
      no_value_found.search_steps = search_steps;
      no_value_found.value = value;
      return no_value_found;
    }

    if (value == value_to_find) {
      if (nearest == search_option::NEAREST_DONT_EXIST) {
        auto dont_exist = value + 1;
        auto has_value = false;
        for (array_index j = i + 1; j < SIZE; ++j) {
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
        dont_exist_found.index = i;
        dont_exist_found.search_steps = search_steps;
        dont_exist_found.value = dont_exist;
        return dont_exist_found;
      }

      search_result value_found{};
      value_found.index = i;
      value_found.has_result = true;
      value_found.search_steps = search_steps;
      value_found.value = value;
      return value_found;
    }

    last_value = value;
  }

  search_result no_value_found{};
  no_value_found.index = SIZE;
  no_value_found.search_steps = search_steps;
  no_value_found.value = last_value;
  return no_value_found;
}

template <std::size_t SIZE>
search_result
array_linear_search(std::span<array_value, SIZE> const sorted_array,
                    array_value value_to_find,
                    std::map<array_value, array_index> const &) {
  return array_linear_search_2(sorted_array, value_to_find);
}

} // namespace frank::algo
