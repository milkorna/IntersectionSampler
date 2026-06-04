
#include <cstdlib>
#include <stdexcept>

#include "CommonTypes.h"
#include "Constants.h"

namespace {

double dotImpl(double ax, double ay, double az, double bx, double by,
               double bz) {
  return ax * bx + ay * by + az * bz;
}

Vector3D crossImpl(double ax, double ay, double az, double bx, double by,
                   double bz) {
  return Vector3D{ay * bz - az * by, az * bx - ax * bz, ax * by - ay * bx};
}

} // namespace

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

bool Point3D::isEqualTo(const Point3D &other, const double tolerance) const {
  return (std::abs(x - other.x) < tolerance) &&
         (std::abs(y - other.y) < tolerance) &&
         (std::abs(z - other.z) < tolerance);
}

Point3D Point3D::translated(const Vector3D &offset) const {
  return Point3D{x + offset.getX(), y + offset.getY(), z + offset.getZ()};
}

Vector3D::Vector3D(double xVal, double yVal, double zVal)
    : x(xVal), y(yVal), z(zVal) {
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

Vector3D Vector3D::between(const Point3D &from, const Point3D &to) {
  return Vector3D{to.getX() - from.getX(), to.getY() - from.getY(),
                  to.getZ() - from.getZ()};
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

double dot(const Vector3D &lhs, const Vector3D &rhs) {
  return dotImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                 rhs.getZ());
}

double dot(const Vector3D &lhs, const Direction3D &rhs) {
  return dotImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                 rhs.getZ());
}

double dot(const Direction3D &lhs, const Vector3D &rhs) {
  return dot(rhs, lhs);
}

double dot(const Direction3D &lhs, const Direction3D &rhs) {
  return dotImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                 rhs.getZ());
}

Vector3D cross(const Vector3D &lhs, const Vector3D &rhs) {
  return crossImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                   rhs.getZ());
}

Vector3D cross(const Vector3D &lhs, const Direction3D &rhs) {
  return crossImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                   rhs.getZ());
}

Vector3D cross(const Direction3D &lhs, const Vector3D &rhs) {
  return crossImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                   rhs.getZ());
}

Vector3D cross(const Direction3D &lhs, const Direction3D &rhs) {
  return crossImpl(lhs.getX(), lhs.getY(), lhs.getZ(), rhs.getX(), rhs.getY(),
                   rhs.getZ());
}