#pragma once

#include <istream>
#include <string>

#include "InputData.h"

class DataReader {
public:
  explicit DataReader(std::string filename);

  InputData read() const;

private:
  Point3D readPoint(std::istream &input) const;
  void readPlane(std::istream &input, PlaneInputData &planeData) const;
  void readShape(std::istream &input, ShapeInputData &shapeData) const;

private:
  std::string m_filename;
};