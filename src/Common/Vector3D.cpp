#include "Vector3D.h"

#include "Common/AppError.h"
#include "Constants.h"
#include "Direction3D.h"
#include "Point3D.h"

Vector3D::Vector3D(double xVal, double yVal, double zVal)
    : m_x(xVal), m_y(yVal), m_z(zVal) {
}

Vector3D::Vector3D(const Point3D &from, const Point3D &to)
    : m_x(to.getX() - from.getX()), m_y(to.getY() - from.getY()),
      m_z(to.getZ() - from.getZ()) {
}

double Vector3D::getX() const {
  return m_x;
}

double Vector3D::getY() const {
  return m_y;
}

double Vector3D::getZ() const {
  return m_z;
}

bool Vector3D::isZero(double tolerance) const {
  return getLength() < tolerance;
}

Vector3D Vector3D::operator+(const Vector3D &other) const {
  return Vector3D{m_x + other.m_x, m_y + other.m_y, m_z + other.m_z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
  return Vector3D{m_x - other.m_x, m_y - other.m_y, m_z - other.m_z};
}

Vector3D Vector3D::operator*(double scalar) const {
  return Vector3D{m_x * scalar, m_y * scalar, m_z * scalar};
}

Vector3D Vector3D::operator/(double scalar) const {
  if (std::abs(scalar) < constants::MinLength) {
    throw AppError(ErrorCode::InvalidArguments, "Division by zero.");
  }

  return Vector3D{m_x / scalar, m_y / scalar, m_z / scalar};
}

double Vector3D::getLength() const {
  return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector3D Vector3D::normalized() const {
  const double length = getLength();

  if (length < constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Cannot normalize zero-length vector.");
  }

  return Vector3D{m_x / length, m_y / length, m_z / length};
}

double Vector3D::dot(const Vector3D &other) const {
  return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

double Vector3D::dot(const Direction3D &other) const {
  return m_x * other.getX() + m_y * other.getY() + m_z * other.getZ();
}

Vector3D Vector3D::cross(const Vector3D &other) const {
  return Vector3D{m_y * other.m_z - m_z * other.m_y,
                  m_z * other.m_x - m_x * other.m_z,
                  m_x * other.m_y - m_y * other.m_x};
}
