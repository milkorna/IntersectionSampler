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

class Vector3D {
public:
  Vector3D() = default;
  Vector3D(double xVal, double yVal, double zVal);

  double getX() const;
  double getY() const;
  double getZ() const;

  static Vector3D between(const Point3D &from, const Point3D &to);

  bool isZero(double tolerance = 1e-12) const;
  double getLength() const;

  Vector3D normalized() const;

  Vector3D operator+(const Vector3D &other) const;
  Vector3D operator-(const Vector3D &other) const;
  Vector3D operator*(double scalar) const;
  Vector3D operator/(double scalar) const;

private:
  double x{0.0};
  double y{0.0};
  double z{0.0};
};

class Direction3D {
public:
  Direction3D() = default;
  explicit Direction3D(double xVal, double yVal, double zVal);
  explicit Direction3D(const Vector3D &vector);

  double getX() const;
  double getY() const;
  double getZ() const;

  Vector3D toVector() const;

private:
  void setNormalized(double xVal, double yVal, double zVal);

private:
  double x{1.0};
  double y{0.0};
  double z{0.0};
};

double dot(const Vector3D &lhs, const Vector3D &rhs);
double dot(const Vector3D &lhs, const Direction3D &rhs);
double dot(const Direction3D &lhs, const Vector3D &rhs);
double dot(const Direction3D &lhs, const Direction3D &rhs);

Vector3D cross(const Vector3D &lhs, const Vector3D &rhs);
Vector3D cross(const Vector3D &lhs, const Direction3D &rhs);
Vector3D cross(const Direction3D &lhs, const Vector3D &rhs);
Vector3D cross(const Direction3D &lhs, const Direction3D &rhs);