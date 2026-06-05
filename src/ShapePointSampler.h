#pragma once

#include "Shapes.h"

#include <cstddef>
#include <utility>
#include <vector>

#include "Common/Direction3D.h"
#include "Common/Plane.h"
#include "Common/Point3D.h"
#include "Common/Vector3D.h"

struct CylinderSample {
  std::pair<Point3D, Point3D> axis;
  std::vector<Point3D> bottomBasePoints;
  std::vector<Point3D> topBasePoints;
};

struct ConeSample {
  std::pair<Point3D, Point3D> axis;
  std::vector<Point3D> basePoints;
  std::vector<Point3D> generatrixPoints;
  Point3D apex;
};

class CylinderPointSampler {
public:
  explicit CylinderPointSampler(const Cylinder &cylinder);

  CylinderSample sample(size_t pointCount) const;

private:
  Cylinder m_cylinder;
};

class ConePointSampler {
public:
  explicit ConePointSampler(const Cone &cone);

  ConeSample sample(size_t pointCount) const;

private:
  Cone m_cone;
};