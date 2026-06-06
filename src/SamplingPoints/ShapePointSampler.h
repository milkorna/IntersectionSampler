#pragma once

#include <utility>

#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "Common/Point3D.h"

/**
 * @brief Sampled cylinder points
 */
struct CylinderSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray bottomBasePoints;
  Point3DArray topBasePoints;
};

/**
 * @brief Sampled cone points
 */
struct ConeSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray basePoints;
  Point3DArray generatrixPoints;
  Point3D apex;
};

/**
 * @brief Traits for shape sample type and sampling implementation
 *
 * @tparam Shape Shape type
 */
template <typename Shape> struct ShapeSampleTraits;

/**
 * @brief Sampling traits for cylinder
 */
template <> struct ShapeSampleTraits<Cylinder> {
  using Sample = CylinderSample;

  /**
   * @brief Samples cylinder points
   *
   * @param[in] cylinder Cylinder to sample
   *
   * @return Cylinder sample data
   */
  static CylinderSample sample(const Cylinder &cylinder);
};

/**
 * @brief Sampling traits for cone
 */
template <> struct ShapeSampleTraits<Cone> {
  using Sample = ConeSample;

  /**
   * @brief Samples cone points
   *
   * @param[in] cone Cone to sample
   *
   * @return Cone sample data
   */
  static ConeSample sample(const Cone &cone);
};

/**
 * @brief Samples points on a shape
 *
 * @tparam Shape Shape type
 */
template <typename Shape> class ShapePointSampler {
public:
  using Sample = typename ShapeSampleTraits<Shape>::Sample;

  /**
   * @brief Creates shape point sampler
   *
   * @param[in] shape Shape to sample
   */
  explicit ShapePointSampler(const Shape &shape) : m_shape(shape) {
  }

  /**
   * @brief Samples shape points
   *
   * @return Shape sample data
   */
  Sample sample() const {
    return ShapeSampleTraits<Shape>::sample(m_shape);
  }

private:
  Shape m_shape;
};

using CylinderPointSampler = ShapePointSampler<Cylinder>;
using ConePointSampler = ShapePointSampler<Cone>;