#include "Cylinder.h"

#include <stdexcept>

#include "Point3D.h"
#include "ValidationUtils.h"

Cylinder::Cylinder(const ShapeInputData &inputData)
    : Cylinder(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cylinder) {
    throw std::invalid_argument("ShapeInputData type is not Cylinder.");
  }
}

Cylinder::Cylinder(const Point3D &firstBaseCenterVal,
                   const Point3D &secondBaseCenterVal, const double radiusVal)
    : firstBaseCenter(firstBaseCenterVal),
      secondBaseCenter(secondBaseCenterVal), radius(radiusVal) {
  geometry_validation::validateRadius(radius);
  geometry_validation::validateDifferentPoints(
      firstBaseCenter, secondBaseCenter,
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