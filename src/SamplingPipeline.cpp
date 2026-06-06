#include "SamplingPipeline.h"

#include <iostream>
#include <stdexcept>
#include <utility>

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

void SamplingPipeline::run() const {
  const DataReader reader(m_inputFile.string());
  const InputData data = reader.getData();

  const DataWriter writer(m_outputDirectory);

  printInfo(data);

  const Plane plane(data.plane);

  writePlaneSample(plane, writer);
  writeShapeSample(data.shape, writer);
  writeIntersectionSample(plane, data.shape, writer);

  std::cout << "\nOutput files directory: " << m_outputDirectory << '\n';
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

  throw std::runtime_error("Unsupported shape type.");
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

std::string SamplingPipeline::shapeTypeToString(ShapeType type) {
  switch (type) {
  case ShapeType::Cylinder:
    return "cylinder";

  case ShapeType::Cone:
    return "cone";
  }

  return "unknown";
}

void SamplingPipeline::printPoint(const Point3D &point) {
  std::cout << '(' << point.getX() << ", " << point.getY() << ", "
            << point.getZ() << ')';
}

void SamplingPipeline::printInfo(const InputData &data) {
  std::cout << "Plane points:\n";
  printPoint(data.plane.firstPoint);
  std::cout << '\n';

  printPoint(data.plane.secondPoint);
  std::cout << '\n';

  printPoint(data.plane.thirdPoint);
  std::cout << "\n\n";

  std::cout << "Shape type: " << shapeTypeToString(data.shape.type) << '\n';

  std::cout << "First point: ";
  printPoint(data.shape.firstPoint);
  std::cout << '\n';

  std::cout << "Second point: ";
  printPoint(data.shape.secondPoint);
  std::cout << '\n';

  std::cout << "Radius: " << data.shape.radius << '\n';
}