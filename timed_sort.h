#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <span>

namespace frank::algo {

template <std::size_t SIZE> void timed_sort(std::span<int, SIZE> &sorted_data) {
  std::cerr << "Sorting...\n";
  auto sort_start = std::chrono::high_resolution_clock::now();

  // C ::qsort is much slower (such as twice as slow)
  std::sort(sorted_data.begin(), sorted_data.end());
  auto sort_stop = std::chrono::high_resolution_clock::now();
  auto sort_duration =
      duration_cast<std::chrono::microseconds>(sort_stop - sort_start);
  std::cerr << "Sort duration: " << sort_duration.count() << " us\n";
}

} // namespace frank::algo
