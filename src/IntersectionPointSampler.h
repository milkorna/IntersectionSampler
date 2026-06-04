#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "CommonTypes.h"
#include "Plane.h"
#include "Shapes.h"

class IIntersectionSampler {
public:
  virtual ~IIntersectionSampler() = default;

  virtual std::vector<Point3D> sample(size_t pointCount) const = 0;
};

class ConeIntersectionSampler final : public IIntersectionSampler {
public:
  ConeIntersectionSampler(const Plane &plane, const Cone &cone);

  std::vector<Point3D> sample(size_t pointCount) const override;

private:
  Plane m_plane;
  Cone m_cone;
};

class CylinderIntersectionSampler final : public IIntersectionSampler {
public:
  CylinderIntersectionSampler(const Plane &plane, const Cylinder &cylinder);

  std::vector<Point3D> sample(size_t pointCount) const override;

private:
  Plane m_plane;
  Cylinder m_cylinder;
};

class IntersectionPointSampler {
public:
  explicit IntersectionPointSampler(
      std::unique_ptr<IIntersectionSampler> sampler);

  std::vector<Point3D> sample(size_t pointCount) const;

private:
  std::unique_ptr<IIntersectionSampler> m_sampler;
};