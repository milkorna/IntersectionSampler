#pragma once

#include <filesystem>
#include <fstream>
#include <ostream>
#include <string>

#include "Common/Point3D.h"
#include "SamplingPoints/PlanePointSampler.h"
#include "SamplingPoints/ShapePointSampler.h"

/**
 * @brief Writes sampled points to output files
 */
class DataWriter {
public:
  /**
   * @brief Creates a writer for output directory
   *
   * @param[in] outputDirectory Directory for generated files
   */
  explicit DataWriter(std::filesystem::path outputDirectory);

  /**
   * @brief Writes intersection points
   *
   * @param[in] points Intersection points
   */
  void writeIntersectionPoints(const Point3DArray &points) const;

  /**
   * @brief Writes plane sample
   *
   * @param[in] sample Plane sample data
   */
  void writePlaneSample(const PlaneSample &sample) const;

  /**
   * @brief Writes cone sample
   *
   * @param[in] sample Cone sample data
   */
  void writeShapeSample(const ConeSample &sample) const;

  /**
   * @brief Writes cylinder sample
   *
   * @param[in] sample Cylinder sample data
   */
  void writeShapeSample(const CylinderSample &sample) const;

private:
  /**
   * @brief Opens output file
   *
   * @param[in] filename Output file name
   *
   * @return Output file stream
   */
  std::ofstream openOutputFile(const std::string &filename) const;

  /**
   * @brief Writes point coordinates to stream
   *
   * @param[in,out] output Output stream
   * @param[in] point Point to write
   */
  static void writePoint(std::ostream &output, const Point3D &point);

  /**
   * @brief Writes point range to stream
   *
   * @param[in,out] output Output stream
   * @param[in] points Points to write
   */
  static void writePointRange(std::ostream &output, const Point3DArray &points);

  /**
   * @brief Writes section header to stream
   *
   * @param[in,out] output Output stream
   * @param[in] sectionName Section name
   */
  static void writeSectionHeader(std::ostream &output,
                                 const std::string &sectionName);

private:
  static const std::string m_planePointsFilename;
  static const std::string m_intersectionPointsFilename;
  static const std::string m_coneShapePointsFilename;
  static const std::string m_cylinderShapePointsFilename;

  std::filesystem::path m_outputDirectory;
};