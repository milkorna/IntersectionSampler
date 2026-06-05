#include "DataWriter.h"

#include <fstream>
#include <stdexcept>

void DataWriter::writePoints(const std::string &filename,
                             const std::vector<Point3D> &points) {
  std::ofstream output(filename);

  if (!output.is_open()) {
    throw std::runtime_error("Failed to open output file: " + filename);
  }

  writePointRange(output, points);
}

void DataWriter::writePlaneSample(const std::string &filename,
                                  const PlaneSample &sample) {
  std::ofstream output(filename);

  if (!output.is_open()) {
    throw std::runtime_error("Failed to open output file: " + filename);
  }

  writeSectionHeader(output, "origin");
  writePoint(output, sample.origin);

  output << '\n';

  writeSectionHeader(output, "points");
  writePointRange(output, sample.points);
}

void DataWriter::writeConeSample(const std::string &filename,
                                 const ConeSample &sample) {
  std::ofstream output(filename);

  if (!output.is_open()) {
    throw std::runtime_error("Failed to open output file: " + filename);
  }

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

void DataWriter::writeCylinderSample(const std::string &filename,
                                     const CylinderSample &sample) {
  std::ofstream output(filename);

  if (!output.is_open()) {
    throw std::runtime_error("Failed to open output file: " + filename);
  }

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

void DataWriter::writePoint(std::ostream &output, const Point3D &point) {
  output << point.getX() << ' ' << point.getY() << ' ' << point.getZ() << '\n';
}

void DataWriter::writePointRange(std::ostream &output,
                                 const std::vector<Point3D> &points) {
  for (const Point3D &point : points) {
    writePoint(output, point);
  }
}

void DataWriter::writeSectionHeader(std::ostream &output,
                                    const std::string &sectionName) {
  output << sectionName << '\n';
}