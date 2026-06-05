#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "Common/Point3D.h"
#include "PlanePointSampler.h"
#include "ShapePointSampler.h"

class DataWriter {
public:
  static void writePoints(const std::string &filename,
                          const std::vector<Point3D> &points);

  static void writePlaneSample(const std::string &filename,
                               const PlaneSample &sample);

  static void writeConeSample(const std::string &filename,
                              const ConeSample &sample);

  static void writeCylinderSample(const std::string &filename,
                                  const CylinderSample &sample);

private:
  static void writePoint(std::ostream &output, const Point3D &point);

  static void writePointRange(std::ostream &output,
                              const std::vector<Point3D> &points);

  static void writeSectionHeader(std::ostream &output,
                                 const std::string &sectionName);
};