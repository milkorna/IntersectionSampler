#pragma once

#include <memory>

#include "Common/Plane.h"
#include "IO/InputData.h"
#include "IntersectionPointSampler.h"

/**
 * @brief Creates intersection samplers by shape type
 */
class IntersectionPointSamplerFactory {
public:
  /**
   * @brief Creates intersection sampler for parsed shape data
   *
   * @param[in] plane Section plane
   * @param[in] shapeData Parsed shape input data
   *
   * @return Created intersection sampler
   */
  static std::unique_ptr<IIntersectionSampler>
  create(const Plane &plane, const ShapeInputData &shapeData);

private:
  /**
   * @brief Creates cone intersection sampler
   *
   * @param[in] plane Section plane
   * @param[in] shapeData Parsed shape input data
   *
   * @return Created cone intersection sampler
   */
  static std::unique_ptr<IIntersectionSampler>
  createConeIntersectionSampler(const Plane &plane,
                                const ShapeInputData &shapeData);

  /**
   * @brief Creates cylinder intersection sampler
   *
   * @param[in] plane Section plane
   * @param[in] shapeData Parsed shape input data
   *
   * @return Created cylinder intersection sampler
   */
  static std::unique_ptr<IIntersectionSampler>
  createCylinderIntersectionSampler(const Plane &plane,
                                    const ShapeInputData &shapeData);
};