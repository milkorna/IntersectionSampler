#pragma once

#include <istream>
#include <string>

#include "InputData.h"

class DataReader {
public:
  explicit DataReader(std::string filename);

  InputData getData() const;

private:
  Point3D getPoint(std::istream &input) const;
  PlaneInputData getPlaneData(std::istream &input) const;
  ShapeInputData getShapeData(std::istream &input) const;

private:
  std::string m_filename;
};