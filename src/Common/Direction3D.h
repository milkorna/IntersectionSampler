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
  void setNormalized(double xVal, double yVal, double zVal);

private:
  double x{1.0};
  double y{0.0};
  double z{0.0};
};