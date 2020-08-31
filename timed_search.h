#pragma once

#include <chrono>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <span>

#include "array_binary_search.h"
#include "array_linear_search.h"
#include "search_result.h"

namespace frank::algo {

template <std::size_t SIZE>
using search_func = search_result (*)(std::span<int, SIZE> const sorted_array,
                                      int value_to_find);

template <std::size_t SIZE>
search_result timed_search(std::span<int, SIZE> const sorted_data,
                           std::string message, int value_to_find,
                           search_func<SIZE> untimed_search) {
  constexpr auto FIELD_WIDTH = 9;

  std::cerr << "Searching (" << message << ")...\n";
  auto clock_start = ::clock();
  auto start = std::chrono::high_resolution_clock::now();
  auto results = untimed_search(sorted_data, value_to_find);
  auto stop = std::chrono::high_resolution_clock::now();
  auto clock_stop = ::clock();
  auto duration = duration_cast<std::chrono::microseconds>(stop - start);
  auto clock_duration = clock_stop - clock_start;
  std::cerr << "  | " << message
            << " search duration: " << std::setw(FIELD_WIDTH)
            << duration.count() << " us\n";
  std::cerr << "  | " << message
            << "    search clock: " << std::setw(FIELD_WIDTH) << clock_duration
            << " ticks\n";
  std::cerr << "  | " << message
            << "    search steps: " << std::setw(FIELD_WIDTH)
            << results.search_steps << '\n';
  if (!results.has_result)
    return results;

  std::cerr << "  | " << message
            << "    search value: " << std::setw(FIELD_WIDTH) << results.value
            << '\n';
  return results;
}

template <std::size_t SIZE>
search_result timed_linear_search(std::span<int, SIZE> const sorted_data,
                                  std::string message, int value_to_find) {
  return timed_search(sorted_data, message, value_to_find, array_linear_search);
}

template <std::size_t SIZE>
search_result timed_binary_search(std::span<int, SIZE> const sorted_data,
                                  std::string message, int value_to_find) {
  return timed_search(sorted_data, message, value_to_find, array_binary_search);
}

} // namespace frank::algo
