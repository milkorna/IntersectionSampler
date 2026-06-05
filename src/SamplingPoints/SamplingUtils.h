#pragma once

#include <vector>

#include "Common/Direction3D.h"
#include "Common/Point3D.h"
#include "Common/Vector3D.h"

namespace sampling_utils {

Direction3D perpendicular(const Direction3D &axisDirection);

Vector3D radial(const Direction3D &xDir, const Direction3D &yDir,
                const double theta);

bool isInRange(const double value, const double minValue,
               const double maxValue);

std::vector<double> solveTrigonometricEquation(const double a, const double b,
                                               const double c);

Point3DArray sampleFiniteLine(const Point3D &startPoint,
                              const Vector3D &direction, const double length,
                              const size_t pointCount);

} // namespace sampling_utils
