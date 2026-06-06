#pragma once

#include <ostream>

#include "Common/Point3D.h"

/**
 * @brief Input data numeric limits
 */
namespace input_limits {

/**
 * @brief Minimum allowed coordinate value
 */
inline constexpr double MinCoordinate = -10.0;

/**
 * @brief Maximum allowed coordinate value
 */
inline constexpr double MaxCoordinate = 10.0;

/**
 * @brief Minimum allowed radius value
 */
inline constexpr double MinRadius = 0.0;

/**
 * @brief Maximum allowed radius value
 */
inline constexpr double MaxRadius = 5.0;

} // namespace input_limits

/**
 * @brief Plane data parsed from input file
 */
struct PlaneInputData {
  Point3D firstPoint;
  Point3D secondPoint;
  Point3D thirdPoint;
};

/**
 * @brief Supported shape types
 */
enum class ShapeType : unsigned int { Cone = 0, Cylinder };

/**
 * @brief Shape data parsed from input file
 */
struct ShapeInputData {
  ShapeType type;
  Point3D firstPoint;
  Point3D secondPoint;
  double radius{0.0};
};

/**
 * @brief Complete input data parsed from input file
 */
struct InputData {
  PlaneInputData plane;
  ShapeInputData shape;

  /**
   * @brief Prints input data to stream
   *
   * @param[in,out] output Output stream
   */
  void print(std::ostream &output) const;
};
