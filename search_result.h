#pragma once

#include <cstddef>

namespace frank::algo {

using array_index = std::size_t;
using array_value = int;

struct search_result {
  array_index index{};
  array_value value{};
  std::size_t search_steps{};
  bool has_result{};
};

} // namespace frank::algo
