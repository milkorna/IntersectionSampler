#include "IntersectionPointSamplerFactory.h"

#include "Common/AppError.h"
#include "Common/ErrorCode.h"

std::unique_ptr<IIntersectionSampler>
IntersectionPointSamplerFactory::create(const Plane &plane,
                                        const ShapeInputData &shapeData) {
  switch (shapeData.type) {
  case ShapeType::Cone: {
    return createConeIntersectionSampler(plane, shapeData);
  }
  case ShapeType::Cylinder: {
    return createCylinderIntersectionSampler(plane, shapeData);
  }
  }

  throw AppError(ErrorCode::InvalidArguments, "Unsupported shape type.");
}

std::unique_ptr<IIntersectionSampler>
IntersectionPointSamplerFactory::createConeIntersectionSampler(
    const Plane &plane, const ShapeInputData &shapeData) {
  const Cone cone(shapeData);
  return std::make_unique<ConeIntersectionSampler>(plane, cone);
}

std::unique_ptr<IIntersectionSampler>
IntersectionPointSamplerFactory::createCylinderIntersectionSampler(
    const Plane &plane, const ShapeInputData &shapeData) {
  const Cylinder cylinder(shapeData);
  return std::make_unique<CylinderIntersectionSampler>(plane, cylinder);
}