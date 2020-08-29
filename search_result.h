#pragma once

#include <cstddef>

namespace frank::algo {

struct search_result {
  std::size_t array_index{};
  std::size_t search_steps{};
  int value{};
  bool has_result{};
};

} // namespace frank::algo
