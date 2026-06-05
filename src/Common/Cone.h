#pragma once

#include "IO/InputData.h"

class Cone {
public:
  Cone() = default;
  explicit Cone(const ShapeInputData &inputData);
  explicit Cone(const Point3D &baseCenter, const Point3D &apex,
                const double radius);

  Point3D getBaseCenter() const;
  Point3D getApex() const;
  double getRadius() const;

private:
  Point3D baseCenter;
  Point3D apex;
  double radius{0.0};
};
