#pragma once

#include "IO/InputData.h"

class Cone {
public:
  Cone() = default;
  explicit Cone(const ShapeInputData &inputData);
  explicit Cone(const Point3D &baseCenter, const Point3D &apex, double radius);

  Point3D getBaseCenter() const;
  Point3D getApex() const;
  double getRadius() const;

private:
  Point3D baseCenter;
  Point3D apex;
  double radius{0.0};
};

class Cylinder {
public:
  Cylinder() = default;
  explicit Cylinder(const ShapeInputData &inputData);
  explicit Cylinder(const Point3D &firstBaseCenter,
                    const Point3D &secondBaseCenter, double radius);

  Point3D getFirstBaseCenter() const;
  Point3D getSecondBaseCenter() const;
  double getRadius() const;

private:
  Point3D firstBaseCenter;
  Point3D secondBaseCenter;
  double radius{0.0};
};