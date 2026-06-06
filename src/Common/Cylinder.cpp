#include "Cylinder.h"

#include "AppError.h"
#include "Common/Constants.h"
#include "ErrorCode.h"
#include "Point3D.h"

Cylinder::Cylinder(const ShapeInputData &inputData)
    : Cylinder(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cylinder) {
    throw AppError(ErrorCode::ShapeTypeMismatch,
                   "ShapeInputData type is not Cylinder.");
  }
}

Cylinder::Cylinder(const Point3D &firstBaseCenterVal,
                   const Point3D &secondBaseCenterVal, const double radiusVal)
    : firstBaseCenter(firstBaseCenterVal),
      secondBaseCenter(secondBaseCenterVal), radius(radiusVal) {
  if (radius <= constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry, "Radius is too small.");
  }

  if (firstBaseCenter.isEqual(secondBaseCenter, constants::PointTolerance)) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Failed to create Cylinder: base centers are equal.");
  }
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