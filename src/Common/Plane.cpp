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

  origin = inputData.firstPoint;
  normal = Direction3D{normalVector};
  refDir = Direction3D{firstDir};
}

Plane::Plane(const Point3D &originVal, const Direction3D &normalVal,
             const Direction3D &refDirVal)
    : origin(originVal), normal(normalVal), refDir(refDirVal) {
  if (std::abs(normal.dot(refDir)) > constants::ComputationTolerance) {
    throw AppError(
        ErrorCode::InvalidGeometry,
        "Failed to create Plane: normal and refDir are not perpendicular.");
  }
}

Point3D Plane::getOrigin() const {
  return origin;
}

Direction3D Plane::getNormal() const {
  return normal;
}

Direction3D Plane::getRefDir() const {
  return refDir;
}
