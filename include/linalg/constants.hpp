#pragma once

#include <limits>
#include <numbers>

namespace linalg {

constexpr float float_min = std::numeric_limits<float>::min();
constexpr float epsilon   = std::numeric_limits<float>::epsilon();
constexpr float unit      = 1.0F;
constexpr float pi        = std::numbers::pi_v<float>;

constexpr float sqrt_two          = std::numbers::sqrt2_v<float>;
constexpr float one_over_sqrt_two = 1.0F / std::numbers::sqrt2_v<float>;

} // namespace linalg
