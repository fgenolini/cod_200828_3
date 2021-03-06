#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <span>

#include "search_result.h"

namespace frank::algo {

int ascending(void const *a, void const *b) {
  auto va = *(array_value const *)a;
  auto vb = *(array_value const *)b;
  if (va < vb)
    return -1;

  if (va > vb)
    return 1;

  return 0;
}

template <std::size_t SIZE>
void timed_sort(std::span<array_value, SIZE> sorted_data,
                std::span<array_value, SIZE> qsorted_data) {
  std::cerr << "C++ STL sorting...\n";
  auto start_sort = std::chrono::high_resolution_clock::now();
  std::sort(sorted_data.begin(), sorted_data.end());
  auto stop_sort = std::chrono::high_resolution_clock::now();
  auto sort_duration =
      duration_cast<std::chrono::microseconds>(stop_sort - start_sort);
  std::cerr << "  |  sort duration: " << sort_duration.count() << " us\n";

  // C ::qsort is much slower (such as twice as slow) than C++ STL sort
  std::cerr << "C \"Quick\" sorting...\n";
  auto start_qsort = std::chrono::high_resolution_clock::now();
  ::qsort(qsorted_data.data(), qsorted_data.size(), sizeof(int), ascending);
  auto stop_qsort = std::chrono::high_resolution_clock::now();
  auto qsort_duration =
      duration_cast<std::chrono::microseconds>(stop_qsort - start_qsort);
  std::cerr << "  | qsort duration: " << qsort_duration.count() << " us\n";
}

} // namespace frank::algo
