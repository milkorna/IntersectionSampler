#pragma once

#include "Common/Plane.h"
#include "Common/Point3D.h"

/**
 * @brief Sampled plane points
 */
struct PlaneSample {
  Point3D origin;
  Point3DArray points;
};

/**
 * @brief Samples points on a plane
 */
class PlanePointSampler {
public:
  /**
   * @brief Creates plane point sampler
   *
   * @param[in] plane Plane to sample
   */
  explicit PlanePointSampler(const Plane &plane);

  /**
   * @brief Samples plane points
   *
   * @return Plane sample data
   */
  PlaneSample sample() const;

private:
  Plane m_plane;

  /**
   * @brief Default plane grid size
   */
  static constexpr size_t m_gridSize = 9;
};