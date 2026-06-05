#include <stdexcept>

#include "CommonTypes/Point3D.h"
#include "Constants.h"
#include "Shapes.h"

namespace {

void validateRadius(double radius) {
  if (radius <= constants::MinLength) {
    throw std::invalid_argument("Radius must be positive.");
  }
}

void validateDifferentPoints(const Point3D &first, const Point3D &second,
                             const char *message) {
  if (first.isEqualTo(second, constants::PointTolerance)) {
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