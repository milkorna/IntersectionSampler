#pragma once

#include "CommonTypes/Point3D.h"

namespace input_limits {

inline constexpr double MinCoordinate = -10.0;
inline constexpr double MaxCoordinate = 10.0;

inline constexpr double MinRadius = 0.0;
inline constexpr double MaxRadius = 5.0;

} // namespace input_limits

struct PlaneInputData {
  Point3D firstPoint;
  Point3D secondPoint;
  Point3D thirdPoint;
};

enum class ShapeType : unsigned int { Cylinder = 0, Cone };

struct ShapeInputData {
  ShapeType type;
  Point3D firstPoint;
  Point3D secondPoint;
  double radius{0.0};
};

struct InputData {
  PlaneInputData plane;
  ShapeInputData shape;
};

struct InputDataLimits {
  PlaneInputData plane;
  ShapeInputData shape;
};