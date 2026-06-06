#pragma once

#include <filesystem>

#include "Common/Plane.h"
#include "IO/DataWriter.h"
#include "IO/InputData.h"
#include "Status.h"

/**
 * @brief Runs the point sampling pipeline
 */
class SamplingPipeline {
public:
  /**
   * @brief Creates sampling pipeline
   *
   * @param[in] inputFile Path to input file
   * @param[in] outputDirectory Directory for generated output files
   */
  SamplingPipeline(std::filesystem::path inputFile,
                   std::filesystem::path outputDirectory);

  /**
   * @brief Runs sampling pipeline
   *
   * @return Pipeline execution status
   */
  Status run() const;

private:
  /**
   * @brief Samples plane points and writes them to file
   *
   * @param[in] plane Plane to sample
   * @param[in] writer Data writer
   */
  void writePlaneSample(const Plane &plane, const DataWriter &writer) const;

  /**
   * @brief Samples shape points and writes them to file
   *
   * @param[in] shapeData Parsed shape input data
   * @param[in] writer Data writer
   */
  void writeShapeSample(const ShapeInputData &shapeData,
                        const DataWriter &writer) const;

  /**
   * @brief Samples intersection points and writes them to file
   *
   * @param[in] plane Section plane
   * @param[in] shapeData Parsed shape input data
   * @param[in] writer Data writer
   */
  void writeIntersectionSample(const Plane &plane,
                               const ShapeInputData &shapeData,
                               const DataWriter &writer) const;

private:
  std::filesystem::path m_inputFile;
  std::filesystem::path m_outputDirectory;
};