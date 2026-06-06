#include "DataWriter.h"

#include <fstream>

#include "Common/AppError.h"
#include "Common/ErrorCode.h"

const std::string DataWriter::m_planePointsFilename = "plane_points.txt";

const std::string DataWriter::m_intersectionPointsFilename =
    "intersection_points.txt";

const std::string DataWriter::m_coneShapePointsFilename =
    "shape_cone_points.txt";

const std::string DataWriter::m_cylinderShapePointsFilename =
    "shape_cylinder_points.txt";

DataWriter::DataWriter(std::filesystem::path outputDirectory)
    : m_outputDirectory(std::move(outputDirectory)) {
  std::filesystem::create_directories(m_outputDirectory);
}

void DataWriter::writeIntersectionPoints(const Point3DArray &points) const {
  std::ofstream output = openOutputFile(m_intersectionPointsFilename);

  writePointRange(output, points);
}

void DataWriter::writePlaneSample(const PlaneSample &sample) const {
  std::ofstream output = openOutputFile(m_planePointsFilename);

  writeSectionHeader(output, "origin");
  writePoint(output, sample.origin);

  output << '\n';

  writeSectionHeader(output, "points");
  writePointRange(output, sample.points);
}

void DataWriter::writeShapeSample(const ConeSample &sample) const {
  std::ofstream output = openOutputFile(m_coneShapePointsFilename);

  writeSectionHeader(output, "axis");
  writePoint(output, sample.axis.first);
  writePoint(output, sample.axis.second);

  output << '\n';

  writeSectionHeader(output, "apex");
  writePoint(output, sample.apex);

  output << '\n';

  writeSectionHeader(output, "base");
  writePointRange(output, sample.basePoints);

  output << '\n';

  writeSectionHeader(output, "generatrix");
  writePointRange(output, sample.generatrixPoints);
}

void DataWriter::writeShapeSample(const CylinderSample &sample) const {
  std::ofstream output = openOutputFile(m_cylinderShapePointsFilename);

  writeSectionHeader(output, "axis");
  writePoint(output, sample.axis.first);
  writePoint(output, sample.axis.second);

  output << '\n';

  writeSectionHeader(output, "bottom_base");
  writePointRange(output, sample.bottomBasePoints);

  output << '\n';

  writeSectionHeader(output, "top_base");
  writePointRange(output, sample.topBasePoints);
}

std::ofstream DataWriter::openOutputFile(const std::string &filename) const {
  const std::filesystem::path outputFile = m_outputDirectory / filename;

  std::ofstream output(outputFile);

  if (!output.is_open()) {
    throw AppError(ErrorCode::FailedToOpenFile,
                   "Failed to open output file: " + outputFile.string());
  }

  return output;
}

void DataWriter::writePoint(std::ostream &output, const Point3D &point) {
  output << point.getX() << ' ' << point.getY() << ' ' << point.getZ() << '\n';
}

void DataWriter::writePointRange(std::ostream &output,
                                 const Point3DArray &points) {
  for (const Point3D &point : points) {
    writePoint(output, point);
  }
}

void DataWriter::writeSectionHeader(std::ostream &output,
                                    const std::string &sectionName) {
  output << sectionName << '\n';
}