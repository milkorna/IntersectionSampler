#include "Point3D.h"
#include "Vector3D.h"

Point3D::Point3D(double xVal, double yVal, double zVal)
    : m_x(xVal), m_y(yVal), m_z(zVal) {
}

double Point3D::getX() const {
  return m_x;
}

double Point3D::getY() const {
  return m_y;
}

double Point3D::getZ() const {
  return m_z;
}

bool Point3D::isEqual(const Point3D &other, const double tolerance) const {
  return (std::abs(m_x - other.m_x) < tolerance) &&
         (std::abs(m_y - other.m_y) < tolerance) &&
         (std::abs(m_z - other.m_z) < tolerance);
}

Point3D Point3D::translated(const Vector3D &offset) const {
  return Point3D{m_x + offset.getX(), m_y + offset.getY(), m_z + offset.getZ()};
}
