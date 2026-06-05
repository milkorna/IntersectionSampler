#pragma once

#include <cmath>

class Point3D;
class Direction3D;

class Vector3D {
public:
  Vector3D() = default;
  Vector3D(const double xVal, const double yVal, const double zVal);
  explicit Vector3D(const Point3D &from, const Point3D &to);

  double getX() const;
  double getY() const;
  double getZ() const;

  bool isZero(double tolerance = 1e-12) const;

  double getLength() const;

  Vector3D normalized() const;

  double dot(const Vector3D &other) const;
  double dot(const Direction3D &other) const;
  Vector3D cross(const Vector3D &other) const;

  Vector3D operator+(const Vector3D &other) const;
  Vector3D operator-(const Vector3D &other) const;
  Vector3D operator*(double scalar) const;
  Vector3D operator/(double scalar) const;

private:
  double x{0.0};
  double y{0.0};
  double z{0.0};
};
