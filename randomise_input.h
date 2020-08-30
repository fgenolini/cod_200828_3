#pragma once

#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <span>

namespace frank::algo {

extern std::random_device rd;
extern std::mt19937 mersenne_twister_engine;

template <std::size_t SIZE>
void randomise_input(std::span<int, SIZE> random_data,
                     std::span<int, SIZE> sorted_data,
                     std::span<int, SIZE> qsorted_data) {
  constexpr auto MAXIMAL_VALUE = std::numeric_limits<int>::max();
  constexpr auto MINIMAL_VALUE = std::numeric_limits<int>::min();

  std::uniform_int_distribution<int> random_distribution(MINIMAL_VALUE,
                                                         MAXIMAL_VALUE);

  std::cerr << "Array length: " << random_data.size() << '\n';
  auto array_count = 3ULL;
  auto memory_used = array_count * random_data.size() * sizeof(int);
  auto memory_used_gb = memory_used / (1024.0 * 1024.0 * 1024.0);
  std::cerr << "Memory used: " << memory_used_gb << " GiB\n";
  std::cerr << "Generating random numbers...\n";
  auto start_random = std::chrono::high_resolution_clock::now();
  std::generate(random_data.begin(), random_data.end(),
                [&]() { return random_distribution(mersenne_twister_engine); });
  auto stop_random = std::chrono::high_resolution_clock::now();
  auto random_duration =
      duration_cast<std::chrono::microseconds>(stop_random - start_random);
  std::cerr << "  | random generation duration: " << random_duration.count()
            << " us\n";

  std::cerr << "Copying...\n";
  auto start_copy = std::chrono::high_resolution_clock::now();

  // Slower than for loop:
  // std::copy(random_data.begin(), random_data.end(), sorted_data.begin());
  for (std::size_t i = 0; i < random_data.size(); ++i) {
    sorted_data[i] = random_data[i];
    qsorted_data[i] = random_data[i];
  }

  auto stop_copy = std::chrono::high_resolution_clock::now();
  auto copy_duration =
      duration_cast<std::chrono::microseconds>(stop_copy - start_copy);
  std::cerr << "  | copy duration: " << copy_duration.count() << " us\n";
}

} // namespace frank::algo
