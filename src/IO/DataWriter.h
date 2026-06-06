#pragma once

#include <filesystem>
#include <ostream>
#include <string>
#include <vector>

#include "Common/Point3D.h"
#include "SamplingPoints/PlanePointSampler.h"
#include "SamplingPoints/ShapePointSampler.h"

class DataWriter {
public:
  explicit DataWriter(std::filesystem::path outputDirectory);

  void writeIntersectionPoints(const Point3DArray &points) const;

  void writePlaneSample(const PlaneSample &sample) const;

  void writeConeSample(const ConeSample &sample) const;

  void writeCylinderSample(const CylinderSample &sample) const;

private:
  std::ofstream openOutputFile(const std::string &filename) const;

  static void writePoint(std::ostream &output, const Point3D &point);

  static void writePointRange(std::ostream &output, const Point3DArray &points);

  static void writeSectionHeader(std::ostream &output,
                                 const std::string &sectionName);

private:
  static const std::string m_planePointsFilename;
  static const std::string m_intersectionPointsFilename;
  static const std::string m_coneShapePointsFilename;
  static const std::string m_cylinderShapePointsFilename;

  std::filesystem::path m_outputDirectory;
};