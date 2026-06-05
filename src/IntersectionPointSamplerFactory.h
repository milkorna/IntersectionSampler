#pragma once

#include <memory>

#include "CommonTypes/Plane.h"
#include "InputData.h"
#include "IntersectionPointSampler.h"

class IntersectionPointSamplerFactory {
public:
  static std::unique_ptr<IIntersectionSampler>
  create(const Plane &plane, const ShapeInputData &shapeData);

private:
  static std::unique_ptr<IIntersectionSampler>
  createConeIntersectionSampler(const Plane &plane,
                                const ShapeInputData &shapeData);

  static std::unique_ptr<IIntersectionSampler>
  createCylinderIntersectionSampler(const Plane &plane,
                                    const ShapeInputData &shapeData);
};