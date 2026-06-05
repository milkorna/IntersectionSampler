#include <stdexcept>

#include "Cone.h"
#include "Point3D.h"
#include "ValidationUtils.h"

#include "IO/InputData.h"

Cone::Cone(const ShapeInputData &inputData)
    : Cone(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cone) {
    throw std::invalid_argument("ShapeInputData type is not Cone.");
  }
}

Cone::Cone(const Point3D &baseCenterVal, const Point3D &apexVal,
           const double radiusVal)
    : baseCenter(baseCenterVal), apex(apexVal), radius(radiusVal) {
  geometry_validation::validateRadius(radius);
  geometry_validation::validateDifferentPoints(
      baseCenter, apex,
      "Failed to create Cone: base center and apex are equal.");
}

Point3D Cone::getBaseCenter() const {
  return baseCenter;
}

Point3D Cone::getApex() const {
  return apex;
}

double Cone::getRadius() const {
  return radius;
}
