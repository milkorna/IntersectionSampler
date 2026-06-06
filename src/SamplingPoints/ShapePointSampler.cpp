#include "ShapePointSampler.h"

#include "Common/Constants.h"
#include "Common/Direction3D.h"
#include "Common/Vector3D.h"
#include "SamplingUtils.h"

namespace {

constexpr size_t basePointCount = 45;
constexpr size_t generatrixPointCount = 45;

Point3DArray sampleCircle(const Point3D &center,
                          const Direction3D &axisDirection, double radius,
                          size_t pointCount) {
  if (pointCount == 0) {
    return {};
  }

  Point3DArray points;
  points.reserve(pointCount);

  const Direction3D xDirection = sampling_utils::perpendicular(axisDirection);
  const Direction3D yDirection = axisDirection.cross(xDirection);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radial =
        sampling_utils::radial(xDirection, yDirection, theta);

    points.push_back(center.translated(radial * radius));
  }

  return points;
}

Point3DArray sampleSegment(const Point3D &start, const Point3D &end,
                           size_t pointCount) {
  if (pointCount == 0) {
    return {};
  }

  if (pointCount == 1) {
    return {start};
  }

  Point3DArray points;
  points.reserve(pointCount);

  const Vector3D offset{start, end};

  for (size_t i = 0; i < pointCount; ++i) {
    const double t =
        static_cast<double>(i) / static_cast<double>(pointCount - 1);

    points.push_back(start.translated(offset * t));
  }

  return points;
}

} // namespace

CylinderSample ShapeSampleTraits<Cylinder>::sample(const Cylinder &cylinder) {
  const Point3D firstBaseCenter = cylinder.getFirstBaseCenter();
  const Point3D secondBaseCenter = cylinder.getSecondBaseCenter();
  const double radius = cylinder.getRadius();

  const Vector3D axis{firstBaseCenter, secondBaseCenter};
  const Direction3D axisDirection{axis};

  CylinderSample sample;
  sample.axis = {firstBaseCenter, secondBaseCenter};
  sample.bottomBasePoints =
      sampleCircle(firstBaseCenter, axisDirection, radius, basePointCount);
  sample.topBasePoints =
      sampleCircle(secondBaseCenter, axisDirection, radius, basePointCount);

  return sample;
}

ConeSample ShapeSampleTraits<Cone>::sample(const Cone &cone) {
  const Point3D baseCenter = cone.getBaseCenter();
  const Point3D apex = cone.getApex();
  const double radius = cone.getRadius();

  const Vector3D axis{apex, baseCenter};
  const Direction3D axisDirection{axis};

  const Direction3D xDirection = sampling_utils::perpendicular(axisDirection);

  const Point3D generatrixBasePoint =
      baseCenter.translated(xDirection.toVector() * radius);

  ConeSample sample;
  sample.axis = {baseCenter, apex};
  sample.apex = apex;
  sample.basePoints =
      sampleCircle(baseCenter, axisDirection, radius, basePointCount);
  sample.generatrixPoints =
      sampleSegment(generatrixBasePoint, apex, generatrixPointCount);

  return sample;
}