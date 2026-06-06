#pragma once

#include <cstddef>
#include <memory>

#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "Common/Plane.h"
#include "Common/Point3D.h"

class IIntersectionSampler {
public:
  virtual ~IIntersectionSampler() = default;

  virtual Point3DArray sample() const = 0;

protected:
  static constexpr size_t m_intersectionPointCount = 100;
};

class ConeIntersectionSampler final : public IIntersectionSampler {
public:
  ConeIntersectionSampler(const Plane &plane, const Cone &cone);

  Point3DArray sample() const override;

private:
  Plane m_plane;
  Cone m_cone;
};

class CylinderIntersectionSampler final : public IIntersectionSampler {
public:
  CylinderIntersectionSampler(const Plane &plane, const Cylinder &cylinder);

  Point3DArray sample() const override;

private:
  Plane m_plane;
  Cylinder m_cylinder;
};

class IntersectionPointSampler {
public:
  explicit IntersectionPointSampler(
      std::unique_ptr<IIntersectionSampler> sampler);

  Point3DArray sample() const;

private:
  std::unique_ptr<IIntersectionSampler> m_sampler;
};