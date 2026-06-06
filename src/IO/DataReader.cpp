#include "DataReader.h"

#include <fstream>
#include <utility>

#include "Common/AppError.h"
#include "Common/Constants.h"
#include "Common/ErrorCode.h"
#include "Common/Point3D.h"
#include "InputData.h"

namespace {

bool isInRange(const double value, const double minValue,
               const double maxValue) {
  return value >= minValue && value <= maxValue;
}

void validateCoordinate(const double value, const std::string &name) {
  if (!isInRange(value, input_limits::MinCoordinate,
                 input_limits::MaxCoordinate)) {
    throw AppError(ErrorCode::InvalidArguments,
                   name + " must be in range [-10.0, 10.0]");
  }
}

void validatePointCoordinates(const Point3D &point) {
  validateCoordinate(point.getX(), "Point x coordinate");
  validateCoordinate(point.getY(), "Point y coordinate");
  validateCoordinate(point.getZ(), "Point z coordinate");
}

void validateRadius(const double radius) {
  if (!isInRange(radius, input_limits::MinRadius, input_limits::MaxRadius)) {
    throw AppError(ErrorCode::InvalidArguments,
                   "Radius must be in range [0.0, 5.0]");
  }

  if (radius <= constants::MinLength) {
    throw AppError(ErrorCode::InvalidArguments, "Radius is too small");
  }
}

} // namespace

DataReader::DataReader(std::string filename) : m_filename(std::move(filename)) {
}

InputData DataReader::getData() const {
  std::ifstream input(m_filename);

  if (!input.is_open()) {
    throw AppError(ErrorCode::FailedToOpenFile,
                   "Failed to open file: " + m_filename);
  }

  InputData data;
  data.plane = getPlaneData(input);
  data.shape = getShapeData(input);

  return data;
}

Point3D DataReader::getPoint(std::istream &input) const {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  if (!(input >> x >> y >> z)) {
    throw AppError(ErrorCode::FailedToReadInputData,
                   "Failed to read point coordinates.");
  }

  const Point3D point{x, y, z};
  validatePointCoordinates(point);

  return point;
}

PlaneInputData DataReader::getPlaneData(std::istream &input) const {
  std::string keyword;

  if (!(input >> keyword)) {
    throw AppError(ErrorCode::FailedToReadInputData,
                   "Failed to read plane keyword.");
  }

  if (keyword != "plane") {
    throw AppError(ErrorCode::InvalidArguments, "Expected keyword 'plane'.");
  }

  PlaneInputData planeData;
  planeData.firstPoint = getPoint(input);
  planeData.secondPoint = getPoint(input);
  planeData.thirdPoint = getPoint(input);

  return planeData;
}

ShapeInputData DataReader::getShapeData(std::istream &input) const {
  std::string keyword;

  if (!(input >> keyword)) {
    throw AppError(ErrorCode::FailedToReadInputData,
                   "Failed to read shape keyword.");
  }

  ShapeInputData shapeData;

  if (keyword == "cylinder") {
    shapeData.type = ShapeType::Cylinder;
  } else if (keyword == "cone") {
    shapeData.type = ShapeType::Cone;
  } else {
    throw AppError(ErrorCode::InvalidArguments,
                   "Expected keyword 'cylinder' or 'cone'.");
  }

  shapeData.firstPoint = getPoint(input);
  shapeData.secondPoint = getPoint(input);

  if (!(input >> shapeData.radius)) {
    throw AppError(ErrorCode::FailedToReadInputData, "Failed to read radius.");
  }

  validateRadius(shapeData.radius);

  return shapeData;
}