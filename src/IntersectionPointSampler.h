#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "Common/Direction3D.h"
#include "Common/Plane.h"
#include "Common/Point3D.h"
#include "Common/Vector3D.h"
#include "Shapes.h"

class IIntersectionSampler {
public:
  virtual ~IIntersectionSampler() = default;

  virtual Point3DArray sample(const size_t pointCount) const = 0;
};

class ConeIntersectionSampler final : public IIntersectionSampler {
public:
  ConeIntersectionSampler(const Plane &plane, const Cone &cone);

  Point3DArray sample(const size_t pointCount) const override;

private:
  Plane m_plane;
  Cone m_cone;
};

class CylinderIntersectionSampler final : public IIntersectionSampler {
public:
  CylinderIntersectionSampler(const Plane &plane, const Cylinder &cylinder);

  Point3DArray sample(const size_t pointCount) const override;

private:
  Plane m_plane;
  Cylinder m_cylinder;
};

class IntersectionPointSampler {
public:
  explicit IntersectionPointSampler(
      std::unique_ptr<IIntersectionSampler> sampler);

  Point3DArray sample(const size_t pointCount) const;

private:
  std::unique_ptr<IIntersectionSampler> m_sampler;
};