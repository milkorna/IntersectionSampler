#include "Cylinder.h"

#include <stdexcept>

#include "Constants.h"
#include "Point3D.h"

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

Cylinder::Cylinder(const ShapeInputData &inputData)
    : Cylinder(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cylinder) {
    throw std::invalid_argument("ShapeInputData type is not Cylinder.");
  }
}

Cylinder::Cylinder(const Point3D &firstBaseCenterVal,
                   const Point3D &secondBaseCenterVal, double radiusVal)
    : firstBaseCenter(firstBaseCenterVal),
      secondBaseCenter(secondBaseCenterVal), radius(radiusVal) {
  validateRadius(radius);
  validateDifferentPoints(firstBaseCenter, secondBaseCenter,
                          "Failed to create Cylinder: base centers are equal.");
}

Point3D Cylinder::getFirstBaseCenter() const {
  return firstBaseCenter;
}

Point3D Cylinder::getSecondBaseCenter() const {
  return secondBaseCenter;
}

double Cylinder::getRadius() const {
  return radius;
}