
#include <chrono>
#include <cstdlib>
#include <iostream>

#include "array_binary_search.h"
#include "large_arrays.h"
#include "randomise_input.h"
#include "select_search_values.h"
#include "timed_sort.h"

int main(int, char *[]) {
  std::span random_data{frank::algo::large_array};
  std::span sorted_data{frank::algo::sorted_array};
  frank::algo::randomise_input(random_data, sorted_data);
  frank::algo::timed_sort(sorted_data);

  int value_to_find{};
  int dont_exist_value_to_find{};
  frank::algo::select_search_values(sorted_data, value_to_find,
                                    dont_exist_value_to_find);

  std::cerr << "Searching (linear)...\n";
  auto start = std::chrono::high_resolution_clock::now();
  auto results_linear =
      frank::algo::array_linear_search(sorted_data, value_to_find);
  auto stop = std::chrono::high_resolution_clock::now();
  auto linear_duration = duration_cast<std::chrono::microseconds>(stop - start);
  std::cerr << "  | Linear search duration: " << linear_duration.count()
            << " us\n";
  std::cerr << "  |    Linear search steps: " << results_linear.search_steps
            << '\n';
  if (results_linear.has_result)
    std::cerr << "  |    Linear search value: " << results_linear.value << '\n';

  std::cerr << "Searching (linear, inexistent value)...\n";
  auto dont_exist_start = std::chrono::high_resolution_clock::now();
  auto results_dont_exit_linear =
      frank::algo::array_linear_search(sorted_data, dont_exist_value_to_find);
  auto dont_exist_stop = std::chrono::high_resolution_clock::now();
  auto dont_exist_duration = duration_cast<std::chrono::microseconds>(
      dont_exist_stop - dont_exist_start);
  std::cerr << "  | Inexistent item linear search duration: "
            << dont_exist_duration.count() << " us\n";
  std::cerr << "  |    Inexistent item linear search steps: "
            << results_dont_exit_linear.search_steps << '\n';
  if (results_dont_exit_linear.has_result)
    std::cerr << "  |    Inexistent item linear search value: "
              << results_dont_exit_linear.value << '\n';

  std::cerr << "Searching (binary)...\n";
  auto binary_start = std::chrono::high_resolution_clock::now();
  auto results_binary =
      frank::algo::array_binary_search(sorted_data, value_to_find);
  auto binary_stop = std::chrono::high_resolution_clock::now();
  auto binary_duration =
      duration_cast<std::chrono::microseconds>(binary_stop - binary_start);
  std::cerr << "  | Binary search duration: " << binary_duration.count()
            << " us\n";
  std::cerr << "  |    Binary search steps: " << results_binary.search_steps
            << '\n';
  if (results_binary.has_result)
    std::cerr << "  |    Binary search value: " << results_binary.value << '\n';

  std::cerr << "Searching (binary, inexistent value)...\n";
  auto dont_exist_binary_start = std::chrono::high_resolution_clock::now();
  auto results_dont_exist_binary =
      frank::algo::array_binary_search(sorted_data, dont_exist_value_to_find);
  auto dont_exist_binary_stop = std::chrono::high_resolution_clock::now();
  auto dont_exist_binary_duration = duration_cast<std::chrono::microseconds>(
      dont_exist_binary_stop - dont_exist_binary_start);
  std::cerr << "  | Inexistent item binary search duration: "
            << dont_exist_binary_duration.count() << " us\n";
  std::cerr << "  |    Inexistent item binary search steps: "
            << results_dont_exist_binary.search_steps << '\n';
  if (results_dont_exist_binary.has_result)
    std::cerr << "  |   Inexistent item binary search value: "
              << results_dont_exist_binary.value << '\n';

  auto success = results_linear.has_result && results_binary.has_result;
  if (!success)
    std::cerr << "Test failed\n";

  auto exit_code = success ? EXIT_SUCCESS : EXIT_FAILURE;
  std::exit(exit_code);
  return exit_code;
}
