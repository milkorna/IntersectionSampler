#pragma once

#include <cmath>

class Vector3D;

class Direction3D {
public:
  Direction3D() = default;
  explicit Direction3D(double xVal, double yVal, double zVal);
  explicit Direction3D(const Vector3D &vector);

  double getX() const;
  double getY() const;
  double getZ() const;

  Vector3D toVector() const;

  double dot(const Direction3D &other) const;
  Direction3D cross(const Direction3D &other) const;
  Vector3D cross(const Vector3D &other) const;

private:
  void normalize(const double xVal, const double yVal, const double zVal);

private:
  double m_x{1.0};
  double m_y{0.0};
  double m_z{0.0};
};