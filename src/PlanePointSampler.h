#pragma once

#include <cstddef>
#include <vector>

#include "Common/Plane.h"
#include "Common/Point3D.h"

struct PlaneSample {
  Point3D origin;
  std::vector<Point3D> points;
};

class PlanePointSampler {
public:
  explicit PlanePointSampler(const Plane &plane);

  PlaneSample sample(size_t gridSize) const;

private:
  Plane m_plane;
};