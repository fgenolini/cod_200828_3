#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <span>

namespace frank::algo {

template <std::size_t SIZE> void timed_sort(std::span<int, SIZE> &sorted_data) {
  std::cerr << "Sorting...\n";
  auto start_sort = std::chrono::high_resolution_clock::now();

  // C ::qsort is much slower (such as twice as slow)
  std::sort(sorted_data.begin(), sorted_data.end());
  auto stop_sort = std::chrono::high_resolution_clock::now();
  auto sort_duration =
      duration_cast<std::chrono::microseconds>(stop_sort - start_sort);
  std::cerr << " | sort duration: " << sort_duration.count() << " us\n";
}

} // namespace frank::algo
