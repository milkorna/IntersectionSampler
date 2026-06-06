#pragma once

#include <filesystem>
#include <string>

#include "Common/Plane.h"
#include "Common/Point3D.h"
#include "IO/DataWriter.h"
#include "IO/InputData.h"
#include "Status.h"

class SamplingPipeline {
public:
  SamplingPipeline(std::filesystem::path inputFile,
                   std::filesystem::path outputDirectory);

  Status run() const;

private:
  void writePlaneSample(const Plane &plane, const DataWriter &writer) const;

  void writeShapeSample(const ShapeInputData &shapeData,
                        const DataWriter &writer) const;

  void writeIntersectionSample(const Plane &plane,
                               const ShapeInputData &shapeData,
                               const DataWriter &writer) const;

  static void printInfo(const InputData &data);
  static void printPoint(const Point3D &point);
  static std::string shapeTypeToString(ShapeType type);

private:
  std::filesystem::path m_inputFile;
  std::filesystem::path m_outputDirectory;
};