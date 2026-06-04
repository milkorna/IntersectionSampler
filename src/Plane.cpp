#include "Plane.h"
#include "Constants.h"
#include <stdexcept>

Plane::Plane(const PlaneInputData &inputData) {

  const Vector3D firstDir =
      Vector3D::between(inputData.secondPoint, inputData.firstPoint);

  const Vector3D secondDir =
      Vector3D::between(inputData.thirdPoint, inputData.firstPoint);

  const Vector3D normalVector = cross(firstDir, secondDir);

  if (normalVector.getLength() < constants::MinLength) {
    throw std::invalid_argument(
        "Failed to create Plane: input points are collinear.");
  }

  origin = inputData.firstPoint;
  normal = Direction3D{normalVector};
  refDir = Direction3D{firstDir};
}

Plane::Plane(const Point3D &originVal, const Direction3D &normalVal,
             const Direction3D &refDirVal)
    : origin(originVal), normal(normalVal), refDir(refDirVal) {
  if (std::abs(dot(normal, refDir)) > constants::ComputationTolerance) {
    throw std::invalid_argument(
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
