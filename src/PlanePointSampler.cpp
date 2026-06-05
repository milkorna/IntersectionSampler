#include "PlanePointSampler.h"

#include <stdexcept>

#include "Common/Vector3D.h"
#include "IO/InputData.h"

PlanePointSampler::PlanePointSampler(const Plane &plane) : m_plane(plane) {
}

PlaneSample PlanePointSampler::sample(size_t gridSize) const {
  if (gridSize < 2) {
    throw std::runtime_error("Plane grid size must be at least 2.");
  }

  PlaneSample sample;
  sample.origin = m_plane.getOrigin();

  sample.points.reserve(gridSize * gridSize);

  const Point3D origin = m_plane.getOrigin();
  const Direction3D refDir = m_plane.getRefDir();
  const Direction3D normal = m_plane.getNormal();

  const Direction3D secondDir{normal.cross(refDir)};

  const double minValue = input_limits::MinCoordinate;
  const double maxValue = input_limits::MaxCoordinate;

  const double step = (maxValue - minValue) / static_cast<double>(gridSize - 1);

  for (size_t i = 0; i < gridSize; ++i) {
    const double u = minValue + step * static_cast<double>(i);

    for (size_t j = 0; j < gridSize; ++j) {
      const double v = minValue + step * static_cast<double>(j);

      const Vector3D offset = refDir.toVector() * u + secondDir.toVector() * v;

      const Point3D point = origin.translated(offset);

      if (!point.isEqualTo(origin)) {
        sample.points.push_back(point);
      }
    }
  }

  return sample;
}