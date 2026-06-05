#include "ShapePointSampler.h"

#include <cmath>

#include "Constants.h"
#include "SamplingUtils.h"

CylinderPointSampler::CylinderPointSampler(const Cylinder &cylinder)
    : m_cylinder(cylinder) {
}

CylinderSample CylinderPointSampler::sample(size_t pointCount) const {
  if (pointCount == 0) {
    return {};
  }

  const Point3D bottomCenter = m_cylinder.getFirstBaseCenter();
  const Point3D topCenter = m_cylinder.getSecondBaseCenter();
  const double radius = m_cylinder.getRadius();

  const Vector3D axis{bottomCenter, topCenter};
  const Direction3D axisDirection{axis};

  const Direction3D xDir =
      sampling_utils::makePerpendicularDirection(axisDirection);
  const Direction3D yDir = axisDirection.cross(xDir);

  CylinderSample sample;
  sample.axis = {bottomCenter, topCenter};

  sample.bottomBasePoints.reserve(pointCount);
  sample.topBasePoints.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radialUnitVector =
        sampling_utils::makeUnitRadialVector(xDir, yDir, theta);
    const Vector3D radiusOffset = radialUnitVector * radius;

    sample.bottomBasePoints.push_back(bottomCenter.translated(radiusOffset));
    sample.topBasePoints.push_back(topCenter.translated(radiusOffset));
  }

  return sample;
}

ConePointSampler::ConePointSampler(const Cone &cone) : m_cone(cone) {
}

ConeSample ConePointSampler::sample(size_t pointCount) const {
  if (pointCount == 0) {
    return {};
  }

  const Point3D baseCenter = m_cone.getBaseCenter();
  const Point3D apex = m_cone.getApex();
  const double radius = m_cone.getRadius();

  const Vector3D axis{apex, baseCenter};
  const Direction3D axisDirection{axis};

  const Direction3D xDir =
      sampling_utils::makePerpendicularDirection(axisDirection);
  const Direction3D yDir = axisDirection.cross(xDir);

  ConeSample sample;
  sample.axis = {baseCenter, apex};
  sample.apex = apex;

  sample.basePoints.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radialUnitVector =
        sampling_utils::makeUnitRadialVector(xDir, yDir, theta);
    const Point3D basePoint = baseCenter.translated(radialUnitVector * radius);

    sample.basePoints.push_back(basePoint);
  }

  if (!sample.basePoints.empty() && pointCount > 0) {
    const Point3D generatrixBasePoint = sample.basePoints.front();
    const Vector3D generatrixVector{apex, generatrixBasePoint};

    sample.generatrixPoints.reserve(pointCount);

    if (pointCount == 1) {
      sample.generatrixPoints.push_back(apex);
    } else {
      for (size_t i = 0; i < pointCount; ++i) {
        const double t =
            static_cast<double>(i) / static_cast<double>(pointCount - 1);

        sample.generatrixPoints.push_back(
            apex.translated(generatrixVector * t));
      }
    }
  }

  return sample;
}