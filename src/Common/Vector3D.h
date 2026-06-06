#pragma once

#include <cmath>

#include "Constants.h"

class Point3D;
class Direction3D;

/**
 * @brief Represents a vector in 3D space
 */
class Vector3D {
public:
  /**
   * @brief Creates a zero vector
   */
  Vector3D() = default;

  /**
   * @brief Creates a vector from coordinates
   *
   * @param[in] xVal X coordinate
   * @param[in] yVal Y coordinate
   * @param[in] zVal Z coordinate
   */
  Vector3D(const double xVal, const double yVal, const double zVal);

  /**
   * @brief Creates a vector from one point to another
   *
   * @param[in] from Start point
   * @param[in] to End point
   */
  explicit Vector3D(const Point3D &from, const Point3D &to);

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
   * @brief Checks if vector length is close to zero
   *
   * @param[in] tolerance Zero length tolerance
   *
   * @return True if vector is close to zero
   */
  bool isZero(double tolerance = constants::MinLength) const;

  /**
   * @brief Gets vector length
   *
   * @return Vector length
   */
  double getLength() const;

  /**
   * @brief Returns normalized vector
   *
   * @return Normalized vector
   */
  Vector3D normalized() const;

  /**
   * @brief Calculates dot product
   *
   * @param[in] other Other vector
   *
   * @return Dot product value
   */
  double dot(const Vector3D &other) const;

  /**
   * @brief Calculates dot product
   *
   * @param[in] other Other direction
   *
   * @return Dot product value
   */
  double dot(const Direction3D &other) const;

  /**
   * @brief Calculates cross product
   *
   * @param[in] other Other vector
   *
   * @return Cross product vector
   */
  Vector3D cross(const Vector3D &other) const;

  /**
   * @brief Adds another vector
   *
   * @param[in] other Other vector
   *
   * @return Sum vector
   */
  Vector3D operator+(const Vector3D &other) const;

  /**
   * @brief Subtracts another vector
   *
   * @param[in] other Other vector
   *
   * @return Difference vector
   */
  Vector3D operator-(const Vector3D &other) const;

  /**
   * @brief Multiplies vector by scalar
   *
   * @param[in] scalar Scalar value
   *
   * @return Scaled vector
   */
  Vector3D operator*(double scalar) const;

  /**
   * @brief Divides vector by scalar
   *
   * @param[in] scalar Scalar value
   *
   * @return Scaled vector
   */
  Vector3D operator/(double scalar) const;

private:
  double m_x{0.0};
  double m_y{0.0};
  double m_z{0.0};
};