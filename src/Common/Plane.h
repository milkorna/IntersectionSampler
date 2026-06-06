#pragma once

#include "Direction3D.h"
#include "Point3D.h"

struct PlaneInputData;

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
  Point3D m_origin;
  Direction3D m_normal;
  Direction3D m_refDir;
};