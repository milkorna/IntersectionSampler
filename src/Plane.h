#pragma once

#include "CommonTypes.h"
#include "InputData.h"

class Plane {
public:
  Plane() = default;
  explicit Plane(const PlaneInputData &inputData);

  Plane(const Point3D &origin, const Direction3D &normal,
        const Direction3D &refDir);

  Point3D getOrigin() const;
  Direction3D getNormal() const;
  Direction3D getRefDir() const;

private:
  Point3D origin;
  Direction3D normal;
  Direction3D refDir;
};