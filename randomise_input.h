#pragma once

#include <cstddef>
#include <iostream>
#include <random>
#include <span>

namespace frank::algo {

extern std::random_device rd;
extern std::mt19937 mersenne_twister_engine;

template <std::size_t SIZE>
void randomise_input(std::span<int, SIZE> random_data,
                     std::span<int, SIZE> sorted_data) {
  constexpr auto MAXIMAL_VALUE = std::numeric_limits<int>::max();
  constexpr auto MINIMAL_VALUE = std::numeric_limits<int>::min();

  std::uniform_int_distribution<int> random_distribution(MINIMAL_VALUE,
                                                         MAXIMAL_VALUE);

  std::cerr << "Array length: " << random_data.size() << '\n';
  std::cerr << "Generating random numbers...\n";
  std::generate(random_data.begin(), random_data.end(),
                [&]() { return random_distribution(mersenne_twister_engine); });
  std::cerr << "Copying...\n";
  for (std::size_t i = 0; i < random_data.size(); ++i)
    sorted_data[i] = random_data[i];
}

} // namespace frank::algo
