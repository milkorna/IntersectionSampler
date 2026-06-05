#pragma once

#include <vector>

#include "CommonTypes/Direction3D.h"
#include "CommonTypes/Point3D.h"
#include "CommonTypes/Vector3D.h"

namespace sampling_utils {

Direction3D makePerpendicularDirection(const Direction3D &axisDirection);

Vector3D makeUnitRadialVector(const Direction3D &xDir, const Direction3D &yDir,
                              double theta);

bool isInRange(double value, double minValue, double maxValue);

std::vector<double> solveTrigonometricEquation(double a, double b, double c);

std::vector<Point3D> sampleFiniteLine(const Point3D &startPoint,
                                      const Vector3D &direction, double length,
                                      size_t pointCount);

} // namespace sampling_utils