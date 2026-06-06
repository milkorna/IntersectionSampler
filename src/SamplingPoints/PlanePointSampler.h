#pragma once

#include "Common/Plane.h"
#include "Common/Point3D.h"

struct PlaneSample {
  Point3D origin;
  Point3DArray points;
};

class PlanePointSampler {
public:
  explicit PlanePointSampler(const Plane &plane);

  PlaneSample sample() const;

private:
  Plane m_plane;

  static constexpr size_t m_gridSize = 9;
};