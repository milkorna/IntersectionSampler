#include "Point3D.h"
#include "Vector3D.h"

Point3D::Point3D(double xVal, double yVal, double zVal)
    : x(xVal), y(yVal), z(zVal) {
}

double Point3D::getX() const {
  return x;
}

double Point3D::getY() const {
  return y;
}

double Point3D::getZ() const {
  return z;
}

bool Point3D::isEqual(const Point3D &other, const double tolerance) const {
  return (std::abs(x - other.x) < tolerance) &&
         (std::abs(y - other.y) < tolerance) &&
         (std::abs(z - other.z) < tolerance);
}

Point3D Point3D::translated(const Vector3D &offset) const {
  return Point3D{x + offset.getX(), y + offset.getY(), z + offset.getZ()};
}
