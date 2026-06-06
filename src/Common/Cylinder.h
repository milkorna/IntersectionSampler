#pragma once

#include "IO/InputData.h"

class Cylinder {
public:
  Cylinder() = default;
  explicit Cylinder(const ShapeInputData &inputData);
  explicit Cylinder(const Point3D &firstBaseCenter,
                    const Point3D &secondBaseCenter, const double radius);

  Point3D getFirstBaseCenter() const;
  Point3D getSecondBaseCenter() const;
  double getRadius() const;

private:
  Point3D m_firstBaseCenter;
  Point3D m_secondBaseCenter;
  double m_radius{0.0};
};