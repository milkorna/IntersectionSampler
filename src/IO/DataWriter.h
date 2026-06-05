#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "Common/Point3D.h"
#include "SamplingPoints/PlanePointSampler.h"
#include "SamplingPoints/ShapePointSampler.h"

class DataWriter {
public:
  static void writeIntersectionPoints(const std::string &filename,
                                      const Point3DArray &points);

  static void writePlaneSample(const std::string &filename,
                               const PlaneSample &sample);

  static void writeConeSample(const std::string &filename,
                              const ConeSample &sample);

  static void writeCylinderSample(const std::string &filename,
                                  const CylinderSample &sample);

private:
  static void writePoint(std::ostream &output, const Point3D &point);

  static void writePointRange(std::ostream &output, const Point3DArray &points);

  static void writeSectionHeader(std::ostream &output,
                                 const std::string &sectionName);
};