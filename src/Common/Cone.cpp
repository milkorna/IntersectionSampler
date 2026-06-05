#include <stdexcept>

#include "Cone.h"
#include "Constants.h"
#include "Cylinder.h"
#include "Point3D.h"

#include "IO/InputData.h"

namespace {

void validateRadius(double radius) {
  if (radius <= constants::MinLength) {
    throw std::invalid_argument("Radius must be positive.");
  }
}

void validateDifferentPoints(const Point3D &first, const Point3D &second,
                             const char *message) {
  if (first.isEqual(second, constants::PointTolerance)) {
    throw std::invalid_argument(message);
  }
}

} // namespace

Cone::Cone(const ShapeInputData &inputData)
    : Cone(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cone) {
    throw std::invalid_argument("ShapeInputData type is not Cone.");
  }
}

Cone::Cone(const Point3D &baseCenterVal, const Point3D &apexVal,
           double radiusVal)
    : baseCenter(baseCenterVal), apex(apexVal), radius(radiusVal) {
  validateRadius(radius);
  validateDifferentPoints(
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
