#include "Plane.h"

#include "AppError.h"
#include "Constants.h"
#include "Direction3D.h"
#include "ErrorCode.h"
#include "IO/InputData.h"
#include "Point3D.h"
#include "Vector3D.h"

Plane::Plane(const PlaneInputData &inputData) {
  const Vector3D firstDir{inputData.secondPoint, inputData.firstPoint};
  const Vector3D secondDir{inputData.thirdPoint, inputData.firstPoint};
  const Vector3D normalVector = firstDir.cross(secondDir);

  if (normalVector.getLength() < constants::MinLength) {
    throw AppError(ErrorCode::InvalidGeometry,
                   "Failed to create Plane: input points are collinear.");
  }

  m_origin = inputData.firstPoint;
  m_normal = Direction3D{normalVector};
  m_refDir = Direction3D{firstDir};
}

Plane::Plane(const Point3D &originVal, const Direction3D &normalVal,
             const Direction3D &refDirVal)
    : m_origin(originVal), m_normal(normalVal), m_refDir(refDirVal) {
  if (std::abs(m_normal.dot(m_refDir)) > constants::ComputationTolerance) {
    throw AppError(
        ErrorCode::InvalidGeometry,
        "Failed to create Plane: normal and refDir are not perpendicular.");
  }
}

Point3D Plane::getOrigin() const {
  return m_origin;
}

Direction3D Plane::getNormal() const {
  return m_normal;
}

Direction3D Plane::getRefDir() const {
  return m_refDir;
}
