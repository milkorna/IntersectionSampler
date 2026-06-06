#include "SamplingPipeline.h"

#include <iostream>
#include <utility>

#include "Common/AppError.h"
#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "IO/DataReader.h"
#include "SamplingPoints/IntersectionPointSampler.h"
#include "SamplingPoints/IntersectionPointSamplerFactory.h"
#include "SamplingPoints/PlanePointSampler.h"
#include "SamplingPoints/ShapePointSampler.h"

SamplingPipeline::SamplingPipeline(std::filesystem::path inputFile,
                                   std::filesystem::path outputDirectory)
    : m_inputFile(std::move(inputFile)),
      m_outputDirectory(std::move(outputDirectory)) {
}

Status SamplingPipeline::run() const {
  try {
    const DataReader reader(m_inputFile.string());
    const InputData data = reader.getData();
    data.print(std::cout);

    const DataWriter writer(m_outputDirectory);

    const Plane plane(data.plane);

    writePlaneSample(plane, writer);
    writeShapeSample(data.shape, writer);
    writeIntersectionSample(plane, data.shape, writer);

    std::cout << "\nOutput files directory: " << m_outputDirectory << '\n';

    return Status::ok();

  } catch (const AppError &error) {
    return Status::error(error.getCode(), error.what());
  } catch (const std::exception &error) {
    return Status::error(ErrorCode::UnknownError, error.what());
  }
}

void SamplingPipeline::writePlaneSample(const Plane &plane,
                                        const DataWriter &writer) const {
  const PlanePointSampler planeSampler(plane);
  const PlaneSample planeSample = planeSampler.sample();

  writer.writePlaneSample(planeSample);
}

void SamplingPipeline::writeShapeSample(const ShapeInputData &shapeData,
                                        const DataWriter &writer) const {
  switch (shapeData.type) {
  case ShapeType::Cone: {
    const Cone cone(shapeData);

    const ConePointSampler shapeSampler(cone);
    const ConeSample coneSample = shapeSampler.sample();

    writer.writeShapeSample(coneSample);
    return;
  }

  case ShapeType::Cylinder: {
    const Cylinder cylinder(shapeData);

    const CylinderPointSampler shapeSampler(cylinder);
    const CylinderSample cylinderSample = shapeSampler.sample();

    writer.writeShapeSample(cylinderSample);
    return;
  }
  }

  throw AppError(ErrorCode::InvalidArguments, "Unsupported shape type.");
}

void SamplingPipeline::writeIntersectionSample(const Plane &plane,
                                               const ShapeInputData &shapeData,
                                               const DataWriter &writer) const {
  const IntersectionPointSampler intersectionSampler(
      IntersectionPointSamplerFactory::create(plane, shapeData));

  const Point3DArray intersectionPoints = intersectionSampler.sample();

  writer.writeIntersectionPoints(intersectionPoints);

  std::cout << "\nIntersection points sample count: "
            << intersectionPoints.size() << '\n';
}
