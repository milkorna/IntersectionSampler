#pragma once

#include <cmath>

class Vector3D;

/**
 * @brief Represents a normalized 3D direction
 */
class Direction3D {
public:
  /**
   * @brief Creates default direction along the X axis
   */
  Direction3D() = default;

  /**
   * @brief Creates a direction from coordinates
   *
   * @param[in] xVal X coordinate
   * @param[in] yVal Y coordinate
   * @param[in] zVal Z coordinate
   */
  explicit Direction3D(double xVal, double yVal, double zVal);

  /**
   * @brief Creates a direction from vector
   *
   * @param[in] vector Source vector
   */
  explicit Direction3D(const Vector3D &vector);

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
   * @brief Converts direction to vector
   *
   * @return Vector
   */
  Vector3D toVector() const;

  /**
   * @brief Calculates dot product with another direction
   *
   * @param[in] other Other direction
   *
   * @return Dot product value
   */
  double dot(const Direction3D &other) const;

  /**
   * @brief Calculates cross product with another direction
   *
   * @param[in] other Other direction
   *
   * @return Direction of cross product
   */
  Direction3D cross(const Direction3D &other) const;

  /**
   * @brief Calculates cross product with vector
   *
   * @param[in] other Other vector
   *
   * @return Cross product vector
   */
  Vector3D cross(const Vector3D &other) const;

private:
  /**
   * @brief Normalizes and stores coordinates
   *
   * @param[in] xVal X coordinate
   * @param[in] yVal Y coordinate
   * @param[in] zVal Z coordinate
   */
  void normalize(const double xVal, const double yVal, const double zVal);

private:
  double m_x{1.0};
  double m_y{0.0};
  double m_z{0.0};
};