#pragma once

#include <filesystem>

#include "Common/Plane.h"
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

private:
  std::filesystem::path m_inputFile;
  std::filesystem::path m_outputDirectory;
};