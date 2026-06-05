#include "Vector3D.h"

#include <stdexcept>

#include "Constants.h"
#include "Direction3D.h"
#include "Point3D.h"

Vector3D::Vector3D(double xVal, double yVal, double zVal)
    : x(xVal), y(yVal), z(zVal) {
}

Vector3D::Vector3D(const Point3D &from, const Point3D &to)
    : x(to.getX() - from.getX()), y(to.getY() - from.getY()),
      z(to.getZ() - from.getZ()) {
}

double Vector3D::getX() const {
  return x;
}

double Vector3D::getY() const {
  return y;
}

double Vector3D::getZ() const {
  return z;
}

bool Vector3D::isZero(double tolerance) const {
  return getLength() < tolerance;
}

Vector3D Vector3D::operator+(const Vector3D &other) const {
  return Vector3D{x + other.x, y + other.y, z + other.z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const {
  return Vector3D{x - other.x, y - other.y, z - other.z};
}

Vector3D Vector3D::operator*(double scalar) const {
  return Vector3D{x * scalar, y * scalar, z * scalar};
}

Vector3D Vector3D::operator/(double scalar) const {
  if (std::abs(scalar) < constants::MinLength) {
    throw std::invalid_argument("Division by zero.");
  }

  return Vector3D{x / scalar, y / scalar, z / scalar};
}

double Vector3D::getLength() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalized() const {
  const double length = getLength();

  if (length < constants::MinLength) {
    throw std::invalid_argument("Cannot normalize zero-length vector.");
  }

  return Vector3D{x / length, y / length, z / length};
}

double Vector3D::dot(const Vector3D &other) const {
  return x * other.x + y * other.y + z * other.z;
}

double Vector3D::dot(const Direction3D &other) const {
  return x * other.getX() + y * other.getY() + z * other.getZ();
}

Vector3D Vector3D::cross(const Vector3D &other) const {
  return Vector3D{y * other.z - z * other.y, z * other.x - x * other.z,
                  x * other.y - y * other.x};
}
