#pragma once

#include <vector>

#include "Common/Direction3D.h"
#include "Common/Point3D.h"
#include "Common/Vector3D.h"

/**
 * @brief Utility functions for point sampling
 */
namespace sampling_utils {

/**
 * @brief Builds a perpendicular direction
 *
 * @param[in] axisDirection Source axis direction
 *
 * @return Direction perpendicular to source direction
 */
Direction3D perpendicular(const Direction3D &axisDirection);

/**
 * @brief Builds radial vector from two basis directions and angle
 *
 * @param[in] xDir First basis direction
 * @param[in] yDir Second basis direction
 * @param[in] theta Angle value
 *
 * @return Radial vector
 */
Vector3D radial(const Direction3D &xDir, const Direction3D &yDir,
                const double theta);

/**
 * @brief Checks if value is inside range
 *
 * @param[in] value Value to check
 * @param[in] minValue Minimum range value
 * @param[in] maxValue Maximum range value
 *
 * @return True if value is inside range
 */
bool isInRange(const double value, const double minValue,
               const double maxValue);

/**
 * @brief Solves trigonometric equation a + b*cos(t) + c*sin(t) = 0
 *
 * @param[in] a Constant coefficient
 * @param[in] b Cosine coefficient
 * @param[in] c Sine coefficient
 *
 * @return Solution angles
 */
std::vector<double> solveTrigonometricEquation(const double a, const double b,
                                               const double c);

/**
 * @brief Samples points on a finite line
 *
 * @param[in] startPoint Start point
 * @param[in] direction Line direction
 * @param[in] length Line length
 * @param[in] pointCount Number of points to sample
 *
 * @return Sampled line points
 */
Point3DArray sampleFiniteLine(const Point3D &startPoint,
                              const Vector3D &direction, const double length,
                              const size_t pointCount);

} // namespace sampling_utils