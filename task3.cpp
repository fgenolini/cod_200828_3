
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <span>

#include "array_binary_search.h"
#include "large_arrays.h"
#include "timed_sort.h"

static std::random_device rd{};
static std::mt19937 mersenne_twister_engine(rd());

int main(int, char *[]) {
  constexpr auto MAXIMAL_VALUE = std::numeric_limits<int>::max();
  constexpr auto MINIMAL_VALUE = std::numeric_limits<int>::min();
  constexpr auto SEARCH_VALUE = 798243;

  std::uniform_int_distribution<int> random_distribution(MINIMAL_VALUE,
                                                         MAXIMAL_VALUE);

  std::span random_data{frank::algo::large_array};
  std::span sorted_data{frank::algo::sorted_array};
  std::cerr << "Array length: " << random_data.size() << '\n';
  std::cerr << "Generating random numbers...\n";
  std::generate(random_data.begin(), random_data.end(),
                [&]() { return random_distribution(mersenne_twister_engine); });
  std::cerr << "First random element: " << random_data[0] << '\n';
  std::cerr << "Copying...\n";
  for (std::size_t i = 0; i < random_data.size(); ++i) {
    sorted_data[i] = random_data[i];
  }

  frank::algo::timed_sort(sorted_data);
  auto min_data = sorted_data[0];
  auto max_data = sorted_data[sorted_data.size() - 1];
  std::cerr << "Min random element: " << min_data << '\n';
  std::cerr << "Max random element: " << max_data << '\n';

  auto value_to_find = ((max_data - min_data) / 2) + SEARCH_VALUE;
  std::cerr << "Value to find: " << value_to_find << '\n';
  constexpr auto NEAREST = frank::algo::search_option::NEAREST;
  auto nearest_results_linear =
      frank::algo::array_linear_search(sorted_data, value_to_find, 0, NEAREST);
  if (nearest_results_linear.has_result) {
    value_to_find = nearest_results_linear.value;
    std::cerr << "Value to find (exists): " << value_to_find << '\n';
  }

  constexpr auto NEAREST_DONT_EXIST =
      frank::algo::search_option::NEAREST_DONT_EXIST;
  auto nearest_dont_exist = frank::algo::array_linear_search(
      sorted_data, value_to_find, 0, NEAREST_DONT_EXIST);
  auto dont_exist_value_to_find = nearest_dont_exist.value;
  std::cerr << "Value to find (does not exist): " << dont_exist_value_to_find
            << '\n';

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

  if (results_linear.has_result || results_binary.has_result)
    std::exit(EXIT_SUCCESS);

  std::exit(EXIT_FAILURE);
  return 1;
}
