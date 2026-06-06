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
    : m_firstBaseCenter(firstBaseCenterVal),
      m_secondBaseCenter(secondBaseCenterVal), m_radius(radiusVal) {
  if (m_radius <= constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry, "Radius is too small.");
  }

  if (m_firstBaseCenter.isEqual(m_secondBaseCenter,
                                constants::PointTolerance)) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Failed to create Cylinder: base centers are equal.");
  }
}

Point3D Cylinder::getFirstBaseCenter() const {
  return m_firstBaseCenter;
}

Point3D Cylinder::getSecondBaseCenter() const {
  return m_secondBaseCenter;
}

double Cylinder::getRadius() const {
  return m_radius;
}