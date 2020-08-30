
#include <random>

#include "randomise_input.h"

namespace frank::algo {

std::random_device rd{};
std::mt19937 mersenne_twister_engine(rd());

} // namespace frank::algo
