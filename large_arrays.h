#pragma once

#include <cstddef>

namespace frank::algo {

// Digits of Pi: 314'159'265
constexpr std::size_t LARGE_NUMBER = 431'415'926ULL;

extern int large_array[LARGE_NUMBER];
extern int sorted_array[LARGE_NUMBER];
extern int qsorted_array[LARGE_NUMBER];

} // namespace frank::algo
