#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "IO/DataReader.h"
#include "IO/DataWriter.h"
#include "SamplingPoints/IntersectionPointSampler.h"
#include "SamplingPoints/IntersectionPointSamplerFactory.h"
#include "SamplingPoints/PlanePointSampler.h"
#include "SamplingPoints/ShapePointSampler.h"

namespace {

constexpr std::size_t IntersectionPointCount = 100;
constexpr std::size_t BasePointCount = 47;
constexpr std::size_t PlaneGridSize = 9;

std::string shapeTypeToString(const ShapeType type) {
  switch (type) {
  case ShapeType::Cylinder:
    return "cylinder";

  case ShapeType::Cone:
    return "cone";
  }

  return "unknown";
}

void printPoint(const Point3D &point) {
  std::cout << '(' << point.getX() << ", " << point.getY() << ", "
            << point.getZ() << ')';
}

void printInfo(const InputData &data) {
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

} // namespace

int main(int argc, char *argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <input_file> <output_directory>\n";
      return 1;
    }

    const std::filesystem::path inputFile = argv[1];
    const std::filesystem::path outputDir = argv[2];

    std::filesystem::create_directories(outputDir);

    const DataReader reader(inputFile.string());
    const InputData data = reader.getData();

    printInfo(data);

    const Plane plane(data.plane);

    const PlanePointSampler planeSampler(plane);
    const PlaneSample planeSample = planeSampler.sample(PlaneGridSize);

    const auto planeOutputFile = outputDir / "plane_points.txt";

    DataWriter::writePlaneSample(planeOutputFile.string(), planeSample);

    switch (data.shape.type) {
    case ShapeType::Cone: {
      const Cone cone(data.shape);

      const ConePointSampler shapeSampler(cone);
      const ConeSample coneSample = shapeSampler.sample(BasePointCount);

      const auto outputFile = outputDir / "shape_cone_points.txt";

      DataWriter::writeConeSample(outputFile.string(), coneSample);
      break;
    }
    case ShapeType::Cylinder: {
      const Cylinder cylinder(data.shape);

      const CylinderPointSampler shapeSampler(cylinder);
      const CylinderSample cylinderSample = shapeSampler.sample(BasePointCount);

      const auto outputFile = outputDir / "shape_cylinder_points.txt";

      DataWriter::writeCylinderSample(outputFile.string(), cylinderSample);
      break;
    }
    }

    const IntersectionPointSampler intersectionSampler(
        IntersectionPointSamplerFactory::create(plane, data.shape));

    const auto intersectionPoints =
        intersectionSampler.sample(IntersectionPointCount);

    const auto intersectionOutputFile = outputDir / "intersection_points.txt";

    DataWriter::writePoints(intersectionOutputFile.string(),
                            intersectionPoints);

    std::cout << "\nOutput files directory: " << outputDir << '\n';
    std::cout << "Intersection points sample count: "
              << intersectionPoints.size() << '\n';

  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}