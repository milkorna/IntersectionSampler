#include "Cone.h"

#include "AppError.h"
#include "Constants.h"
#include "ErrorCode.h"
#include "IO/InputData.h"
#include "Point3D.h"

Cone::Cone(const ShapeInputData &inputData)
    : Cone(inputData.firstPoint, inputData.secondPoint, inputData.radius) {
  if (inputData.type != ShapeType::Cone) {
    throw AppError(ErrorCode::ShapeTypeMismatch,
                   "ShapeInputData type is not Cone.");
  }
}

Cone::Cone(const Point3D &baseCenterVal, const Point3D &apexVal,
           const double radiusVal)
    : m_baseCenter(baseCenterVal), m_apex(apexVal), m_radius(radiusVal) {

  if (m_radius <= constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry, "Radius is too small.");
  }

  if (m_baseCenter.isEqual(m_apex, constants::PointTolerance)) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Failed to create Cone: base center and apex are equal.");
  }
}

Point3D Cone::getBaseCenter() const {
  return m_baseCenter;
}

Point3D Cone::getApex() const {
  return m_apex;
}

double Cone::getRadius() const {
  return m_radius;
}
