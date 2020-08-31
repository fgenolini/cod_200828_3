#pragma once

#include <cstddef>

#include "search_result.h"

namespace frank::algo {

constexpr array_index LARGE_NUMBER = 431'415'926ULL;

extern array_value large_array[LARGE_NUMBER];
extern array_value sorted_array[LARGE_NUMBER];
extern array_value qsorted_array[LARGE_NUMBER];

} // namespace frank::algo
