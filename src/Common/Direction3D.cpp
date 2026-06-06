#include "Direction3D.h"

#include "AppError.h"
#include "Constants.h"
#include "ErrorCode.h"
#include "Vector3D.h"

double Direction3D::getX() const {
  return m_x;
}

double Direction3D::getY() const {
  return m_y;
}

double Direction3D::getZ() const {
  return m_z;
}

Vector3D Direction3D::toVector() const {
  return Vector3D{m_x, m_y, m_z};
}

Direction3D::Direction3D(double xVal, double yVal, double zVal) {
  normalize(xVal, yVal, zVal);
}

Direction3D::Direction3D(const Vector3D &vector) {
  normalize(vector.getX(), vector.getY(), vector.getZ());
}

void Direction3D::normalize(const double xVal, const double yVal,
                            const double zVal) {
  const double length = std::sqrt(xVal * xVal + yVal * yVal + zVal * zVal);

  if (length < constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Failed to create Direction3D from zero-length vector.");
  }

  m_x = xVal / length;
  m_y = yVal / length;
  m_z = zVal / length;
}

double Direction3D::dot(const Direction3D &other) const {
  return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Direction3D Direction3D::cross(const Direction3D &other) const {
  return Direction3D{m_y * other.m_z - m_z * other.m_y,
                     m_z * other.m_x - m_x * other.m_z,
                     m_x * other.m_y - m_y * other.m_x};
}

Vector3D Direction3D::cross(const Vector3D &other) const {
  return Vector3D{m_y * other.getZ() - m_z * other.getY(),
                  m_z * other.getX() - m_x * other.getZ(),
                  m_x * other.getY() - m_y * other.getX()};
}
