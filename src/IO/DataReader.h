#pragma once

#include <istream>
#include <string>

#include "InputData.h"

/**
 * @brief Reads input data from file
 */
class DataReader {
public:
  /**
   * @brief Creates a data reader for input file
   *
   * @param[in] filename Path to input file
   */
  explicit DataReader(std::string filename);

  /**
   * @brief Reads all input data
   *
   * @return Parsed input data
   */
  InputData getData() const;

private:
  /**
   * @brief Reads point coordinates from stream
   *
   * @param[in,out] input Input stream
   *
   * @return Parsed 3D point
   */
  Point3D getPoint(std::istream &input) const;

  /**
   * @brief Reads plane input data from stream
   *
   * @param[in,out] input Input stream
   *
   * @return Parsed plane input data
   */
  PlaneInputData getPlaneData(std::istream &input) const;

  /**
   * @brief Reads shape input data from stream
   *
   * @param[in,out] input Input stream
   *
   * @return Parsed shape input data
   */
  ShapeInputData getShapeData(std::istream &input) const;

private:
  std::string m_filename;
};