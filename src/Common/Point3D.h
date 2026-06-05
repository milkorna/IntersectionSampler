#pragma once

#include <cmath>

class Vector3D;
class Direction3D;

class Point3D {
public:
  Point3D() = default;
  Point3D(double xVal, double yVal, double zVal);

  double getX() const;
  double getY() const;
  double getZ() const;

  bool isEqualTo(const Point3D &other, const double tolerance = 1e-6) const;
  Point3D translated(const Vector3D &offset) const;

private:
  double x{0.0};
  double y{0.0};
  double z{0.0};
};