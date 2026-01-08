#pragma once

#include <limits>
#include <numbers>

namespace Mirage::Math {

constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
constexpr float EPSILON   = std::numeric_limits<float>::epsilon();
constexpr float UNIT      = 1.0F;
constexpr float PI        = std::numbers::pi_v<float>;

constexpr float SQRT_TWO          = std::numbers::sqrt2_v<float>;
constexpr float ONE_OVER_SQRT_TWO = 1.0F / std::numbers::sqrt2_v<float>;

} // namespace Mirage::Math
