
#include <iostream>

#include "large_arrays.h"
#include "randomise_input.h"
#include "select_search_values.h"
#include "setup_bins.h"
#include "timed_search.h"
#include "timed_sort.h"

int main(int, char *[]) {
  std::span random_data{frank::algo::large_array};
  std::span sorted_data{frank::algo::sorted_array};
  std::span qsorted_data{frank::algo::qsorted_array};
  frank::algo::randomise_input(random_data, sorted_data, qsorted_data);
  frank::algo::timed_sort(sorted_data, qsorted_data);

  std::map<frank::algo::array_value, frank::algo::array_index> bins{};
  frank::algo::setup_bins(sorted_data, bins);

  frank::algo::array_value value_to_find{};
  frank::algo::array_value dont_exist_value_to_find{};
  frank::algo::select_search_values(sorted_data, value_to_find,
                                    dont_exist_value_to_find);
  auto results_linear = frank::algo::timed_linear_search(
      sorted_data, "middle value", value_to_find, bins);
  frank::algo::timed_linear_search(sorted_data, "inexistent value",
                                   dont_exist_value_to_find, bins);
  auto results_binary = frank::algo::timed_binary_search(
      sorted_data, "middle value binary", value_to_find, bins);
  frank::algo::timed_binary_search(sorted_data, "inexistent value binary",
                                   dont_exist_value_to_find, bins);
  auto success = results_linear.has_result && results_binary.has_result;
  if (!success)
    std::cerr << "Test failed\n";

  auto exit_code = success ? EXIT_SUCCESS : EXIT_FAILURE;
  std::exit(exit_code);
  return exit_code;
}
