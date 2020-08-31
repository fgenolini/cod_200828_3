#pragma once

#include <map>
#include <span>

#include "large_arrays.h"

namespace frank::algo {

constexpr auto BIN_COUNT = 2048ULL;

extern array_value bin_start[BIN_COUNT];

template <std::size_t SIZE>
void setup_bins(std::span<array_value, SIZE> const sorted_data,
                std::map<array_value, array_index> &bins) {
  auto const bin_size = SIZE / BIN_COUNT;
  auto bin_index = 0ULL;
  for (array_index i = 0ULL; i < SIZE && bin_index < BIN_COUNT; i += bin_size) {
    do {
      array_value value = sorted_data[i];
      if (bins.count(value)) {
        ++i;
        continue;
      }

      bins.emplace(value, i);
      bin_start[bin_index] = value;
      ++bin_index;
      break;
    } while (i < SIZE);
  }

  array_value max_value = sorted_data[SIZE - 1];
  for (auto i = bin_index; i < BIN_COUNT; ++i)
    bin_start[i] = max_value;
}

} // namespace frank::algo
