#pragma once

#include <vector>

#include "Constants.h"

class Vector3D;
class Direction3D;

/**
 * @brief Represents a point in 3D space
 */
class Point3D {
public:
  /**
   * @brief Creates a point at the origin
   */
  Point3D() = default;

  /**
   * @brief Creates a point from coordinates
   *
   * @param[in] xVal X coordinate
   * @param[in] yVal Y coordinate
   * @param[in] zVal Z coordinate
   */
  Point3D(const double xVal, const double yVal, const double zVal);

  /**
   * @brief Gets the X coordinate
   *
   * @return X coordinate
   */
  double getX() const;

  /**
   * @brief Gets the Y coordinate
   *
   * @return Y coordinate
   */
  double getY() const;

  /**
   * @brief Gets the Z coordinate
   *
   * @return Z coordinate
   */
  double getZ() const;

  /**
   * @brief Checks if point is equal to another within tolerance
   *
   * @param[in] other Other point
   * @param[in] tolerance Comparison tolerance
   *
   * @return True if points are equal
   */
  bool isEqual(const Point3D &other,
               const double tolerance = constants::PointTolerance) const;

  /**
   * @brief Returns a point translated by offset vector
   *
   * @param[in] offset Translation vector
   *
   * @return Translated point
   */
  Point3D translated(const Vector3D &offset) const;

private:
  double m_x{0.0};
  double m_y{0.0};
  double m_z{0.0};
};

/**
 * @brief Array of 3D points
 */
using Point3DArray = std::vector<Point3D>;