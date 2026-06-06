#pragma once

#include <cstddef>
#include <memory>

#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "Common/Plane.h"
#include "Common/Point3D.h"

/**
 * @brief Base interface for intersection point samplers
 */
class IIntersectionSampler {
public:
  /**
   * @brief Destгuctor
   */
  virtual ~IIntersectionSampler() = default;

  /**
   * @brief Samples intersection points
   *
   * @return Array of sampled intersection points
   */
  virtual Point3DArray sample() const = 0;

protected:
  /**
   * @brief Default number of intersection points
   */
  static constexpr size_t m_intersectionPointCount = 100;
};

/**
 * @brief Samples intersection points between plane and cone
 */
class ConeIntersectionSampler final : public IIntersectionSampler {
public:
  /**
   * @brief Creates cone intersection sampler
   *
   * @param[in] plane Section plane
   * @param[in] cone Cone to intersect
   */
  ConeIntersectionSampler(const Plane &plane, const Cone &cone);

  /**
   * @brief Samples cone intersection points
   *
   * @return Array of sampled intersection points
   */
  Point3DArray sample() const override;

private:
  Plane m_plane;
  Cone m_cone;
};

/**
 * @brief Samples intersection points between plane and cylinder
 */
class CylinderIntersectionSampler final : public IIntersectionSampler {
public:
  /**
   * @brief Creates cylinder intersection sampler
   *
   * @param[in] plane Section plane
   * @param[in] cylinder Cylinder to intersect
   */
  CylinderIntersectionSampler(const Plane &plane, const Cylinder &cylinder);

  /**
   * @brief Samples cylinder intersection points
   *
   * @return Array of sampled intersection points
   */
  Point3DArray sample() const override;

private:
  Plane m_plane;
  Cylinder m_cylinder;
};

/**
 * @brief Owns selected intersection sampler
 */
class IntersectionPointSampler {
public:
  /**
   * @brief Creates intersection point sampler
   *
   * @param[in] sampler Concrete intersection sampler
   */
  explicit IntersectionPointSampler(
      std::unique_ptr<IIntersectionSampler> sampler);

  /**
   * @brief Samples intersection points
   *
   * @return Array of sampled intersection points
   */
  Point3DArray sample() const;

private:
  std::unique_ptr<IIntersectionSampler> m_sampler;
};