#include <fstream>
#include <stdexcept>
#include <utility>

#include "Common/Constants.h"
#include "DataReader.h"

namespace {

bool isInRange(const double value, const double minValue,
               const double maxValue) {
  return value >= minValue && value <= maxValue;
}

void validateCoordinate(const double value, const std::string &name) {
  if (!isInRange(value, input_limits::MinCoordinate,
                 input_limits::MaxCoordinate)) {
    throw std::runtime_error(name + " must be in range [-10.0, 10.0]");
  }
}

void validatePointCoordinates(const Point3D &point) {
  validateCoordinate(point.getX(), "Point x coordinate");
  validateCoordinate(point.getY(), "Point y coordinate");
  validateCoordinate(point.getZ(), "Point z coordinate");
}

void validateRadius(const double radius) {
  if (!isInRange(radius, input_limits::MinRadius, input_limits::MaxRadius)) {
    throw std::runtime_error("Radius must be in range [0.0, 5.0]");
  }

  if (radius <= constants::MinLength) {
    throw std::runtime_error("Radius is too small");
  }
}

} // namespace

DataReader::DataReader(const std::string &filename)
    : m_filename(std::move(filename)) {
}

InputData DataReader::read() const {
  std::ifstream input(m_filename);

  if (!input.is_open()) {
    throw std::runtime_error("Failed to open file: " + m_filename);
  }

  InputData data;

  readPlane(input, data.plane);
  readShape(input, data.shape);

  return data;
}

Point3D DataReader::readPoint(std::istream &input) const {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  if (!(input >> x >> y >> z)) {
    throw std::runtime_error("Failed to read point coordinates");
  }

  const Point3D point{x, y, z};
  validatePointCoordinates(point);

  return point;
}

void DataReader::readPlane(std::istream &input,
                           PlaneInputData &planeData) const {
  std::string keyword;

  if (!(input >> keyword)) {
    throw std::runtime_error("Failed to read plane keyword");
  }

  if (keyword != "plane") {
    throw std::runtime_error("Expected keyword 'plane'");
  }

  planeData.firstPoint = readPoint(input);
  planeData.secondPoint = readPoint(input);
  planeData.thirdPoint = readPoint(input);
}

void DataReader::readShape(std::istream &input,
                           ShapeInputData &shapeData) const {
  std::string keyword;

  if (!(input >> keyword)) {
    throw std::runtime_error("Failed to read shape keyword");
  }

  if (keyword == "cylinder") {
    shapeData.type = ShapeType::Cylinder;
  } else if (keyword == "cone") {
    shapeData.type = ShapeType::Cone;
  } else {
    throw std::runtime_error("Expected keyword 'cylinder' or 'cone'");
  }

  shapeData.firstPoint = readPoint(input);
  shapeData.secondPoint = readPoint(input);

  if (!(input >> shapeData.radius)) {
    throw std::runtime_error("Failed to read radius");
  }

  validateRadius(shapeData.radius);
}