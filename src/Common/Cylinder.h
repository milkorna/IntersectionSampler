#pragma once

#include "IO/InputData.h"

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