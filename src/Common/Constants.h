#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

/**
 * @brief Common numeric constants
 */
namespace constants {

/**
 * @brief Pi constant
 */
inline constexpr double Pi = M_PI;

/**
 * @brief Tolerance for comparing points
 */
inline constexpr double PointTolerance = 1.0e-6;

/**
 * @brief Tolerance for comparing with zero
 */
inline constexpr double MinLength = 1.0e-12;

/**
 * @brief Tolerance for computation
 */
inline constexpr double ComputationTolerance = 1.0e-9;

} // namespace constants