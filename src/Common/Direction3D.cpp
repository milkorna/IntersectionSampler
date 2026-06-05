#include "Direction3D.h"

#include <stdexcept>

#include "Constants.h"
#include "Vector3D.h"

double Direction3D::getX() const {
  return x;
}

double Direction3D::getY() const {
  return y;
}

double Direction3D::getZ() const {
  return z;
}

Vector3D Direction3D::toVector() const {
  return Vector3D{x, y, z};
}

Direction3D::Direction3D(double xVal, double yVal, double zVal) {
  setNormalized(xVal, yVal, zVal);
}

Direction3D::Direction3D(const Vector3D &vector) {
  setNormalized(vector.getX(), vector.getY(), vector.getZ());
}

void Direction3D::setNormalized(double xVal, double yVal, double zVal) {
  const double length = std::sqrt(xVal * xVal + yVal * yVal + zVal * zVal);

  if (length < constants::MinLength) {
    throw std::invalid_argument(
        "Failed to create Direction3D from zero-length vector.");
  }

  x = xVal / length;
  y = yVal / length;
  z = zVal / length;
}

double Direction3D::dot(const Direction3D &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Direction3D Direction3D::cross(const Direction3D &other) const {
  return Direction3D{y * other.z - z * other.y, z * other.x - x * other.z,
                     x * other.y - y * other.x};
}

Vector3D Direction3D::cross(const Vector3D &other) const {
  return Vector3D{y * other.getZ() - z * other.getY(),
                  z * other.getX() - x * other.getZ(),
                  x * other.getY() - y * other.getX()};
}
