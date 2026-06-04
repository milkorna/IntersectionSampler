#include "SamplingUtils.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "Constants.h"

namespace sampling_utils {

Direction3D makePerpendicularDirection(const Direction3D &axisDirection) {
  const Vector3D xAxis{1.0, 0.0, 0.0};
  const Vector3D yAxis{0.0, 1.0, 0.0};

  Vector3D candidate = cross(axisDirection, xAxis);

  if (candidate.getLength() < constants::MinLength) {
    candidate = cross(axisDirection, yAxis);
  }

  if (candidate.getLength() < constants::MinLength) {
    throw std::runtime_error("Failed to build perpendicular direction.");
  }

  return Direction3D{candidate};
}

Vector3D makeUnitRadialVector(const Direction3D &xDir, const Direction3D &yDir,
                              double theta) {
  return xDir.toVector() * std::cos(theta) + yDir.toVector() * std::sin(theta);
}

bool isInRange(double value, double minValue, double maxValue) {
  return value >= minValue - constants::ComputationTolerance &&
         value <= maxValue + constants::ComputationTolerance;
}

std::vector<double> solveTrigonometricEquation(double a, double b, double c) {
  std::vector<double> angles;

  const double amplitude = std::sqrt(b * b + c * c);

  if (amplitude < constants::ComputationTolerance) {
    return angles;
  }

  const double value = -a / amplitude;

  if (value < -1.0 - constants::ComputationTolerance ||
      value > 1.0 + constants::ComputationTolerance) {
    return angles;
  }

  const double clampedValue = std::clamp(value, -1.0, 1.0);

  const double phase = std::atan2(c, b);
  const double delta = std::acos(clampedValue);

  angles.push_back(phase + delta);

  const bool hasSecondSolution =
      std::abs(delta) > constants::ComputationTolerance &&
      std::abs(delta - constants::Pi) > constants::ComputationTolerance;

  if (hasSecondSolution) {
    angles.push_back(phase - delta);
  }

  return angles;
}

std::vector<Point3D> sampleFiniteLine(const Point3D &startPoint,
                                      const Vector3D &direction, double length,
                                      size_t pointCount) {
  std::vector<Point3D> points;

  if (pointCount == 0) {
    return points;
  }

  if (pointCount == 1) {
    points.push_back(startPoint);
    return points;
  }

  points.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double t =
        static_cast<double>(i) / static_cast<double>(pointCount - 1);

    points.push_back(startPoint.translated(direction * (length * t)));
  }

  return points;
}

} // namespace sampling_utils