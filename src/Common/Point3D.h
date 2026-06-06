#pragma once

#include <cmath>
#include <vector>

class Vector3D;
class Direction3D;

class Point3D {
public:
  Point3D() = default;
  Point3D(double xVal, double yVal, double zVal);

  double getX() const;
  double getY() const;
  double getZ() const;

  bool isEqual(const Point3D &other, const double tolerance = 1e-6) const;
  Point3D translated(const Vector3D &offset) const;

private:
  double m_x{0.0};
  double m_y{0.0};
  double m_z{0.0};
};

using Point3DArray = std::vector<Point3D>;