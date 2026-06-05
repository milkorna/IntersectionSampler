#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace constants {

inline constexpr double Pi = M_PI;

inline constexpr double PointTolerance = 1.0e-6;
inline constexpr double MinLength = 1.0e-12;
inline constexpr double ComputationTolerance = 1.0e-9;

} // namespace constants