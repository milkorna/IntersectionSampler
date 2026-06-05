#pragma once

#include <cstddef>
#include <utility>

#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "Common/Point3D.h"
#include "Common/Vector3D.h"

struct CylinderSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray bottomBasePoints;
  Point3DArray topBasePoints;
};

struct ConeSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray basePoints;
  Point3DArray generatrixPoints;
  Point3D apex;
};

class CylinderPointSampler {
public:
  explicit CylinderPointSampler(const Cylinder &cylinder);

  CylinderSample sample(const size_t pointCount) const;

private:
  Cylinder m_cylinder;
};

class ConePointSampler {
public:
  explicit ConePointSampler(const Cone &cone);

  ConeSample sample(const size_t pointCount) const;

private:
  Cone m_cone;
};