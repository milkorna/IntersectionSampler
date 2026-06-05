#include "IntersectionPointSampler.h"

#include "Constants.h"
#include "SamplingUtils.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace {

struct RevolutionFrame {
  Point3D origin;
  Direction3D axisDirection;
  Direction3D xDir;
  Direction3D yDir;
  double height{0.0};
};

RevolutionFrame makeRevolutionFrame(const Point3D &origin,
                                    const Point3D &axisEnd) {
  const Vector3D axis{origin, axisEnd};
  const double height = axis.getLength();

  if (height < constants::MinLength) {
    throw std::runtime_error("Failed to create revolution frame: zero height.");
  }

  const Direction3D axisDirection{axis};

  const Direction3D xDir =
      sampling_utils::makePerpendicularDirection(axisDirection);

  const Direction3D yDir = axisDirection.cross(xDir);

  return RevolutionFrame{origin, axisDirection, xDir, yDir, height};
}

std::vector<double>
findConeGeneratrixAnglesInPlane(const RevolutionFrame &frame,
                                const Direction3D &planeNormal, double radius) {
  const double k = radius / frame.height;

  const double a = frame.axisDirection.dot(planeNormal);
  const double b = k * frame.xDir.dot(planeNormal);
  const double c = k * frame.yDir.dot(planeNormal);

  return sampling_utils::solveTrigonometricEquation(a, b, c);
}

std::vector<Point3D> sampleConePlaneThroughApex(const RevolutionFrame &frame,
                                                const Plane &plane,
                                                double radius,
                                                size_t pointCount) {
  std::vector<Point3D> points;

  if (pointCount == 0) {
    return points;
  }

  const std::vector<double> angles =
      findConeGeneratrixAnglesInPlane(frame, plane.getNormal(), radius);

  if (angles.empty()) {
    points.push_back(frame.origin);
    return points;
  }

  const size_t pointsPerGeneratrix =
      std::max<size_t>(2, pointCount / angles.size());

  points.reserve(pointsPerGeneratrix * angles.size());

  for (const double theta : angles) {
    const Vector3D radial =
        sampling_utils::makeUnitRadialVector(frame.xDir, frame.yDir, theta);

    for (size_t i = 0; i < pointsPerGeneratrix; ++i) {
      const double t =
          static_cast<double>(i) / static_cast<double>(pointsPerGeneratrix - 1);

      const double axial = frame.height * t;
      const double currentRadius = radius * axial / frame.height;

      const Vector3D offset =
          frame.axisDirection.toVector() * axial + radial * currentRadius;

      points.push_back(frame.origin.translated(offset));
    }
  }

  return points;
}

std::vector<double>
findCylinderGeneratrixAnglesInPlane(const RevolutionFrame &frame,
                                    const Plane &plane, double radius) {
  const double a =
      Vector3D{plane.getOrigin(), frame.origin}.dot(plane.getNormal());

  const double b = radius * frame.xDir.dot(plane.getNormal());
  const double c = radius * frame.yDir.dot(plane.getNormal());

  return sampling_utils::solveTrigonometricEquation(a, b, c);
}

std::vector<Point3D>
sampleCylinderPlaneParallelToAxis(const RevolutionFrame &frame,
                                  const Plane &plane, double radius,
                                  size_t pointCount) {
  std::vector<Point3D> points;

  if (pointCount == 0) {
    return points;
  }

  const std::vector<double> angles =
      findCylinderGeneratrixAnglesInPlane(frame, plane, radius);

  if (angles.empty()) {
    return points;
  }

  const size_t pointsPerGeneratrix =
      std::max<size_t>(2, pointCount / angles.size());

  points.reserve(pointsPerGeneratrix * angles.size());

  for (const double theta : angles) {
    const Vector3D radial =
        sampling_utils::makeUnitRadialVector(frame.xDir, frame.yDir, theta);

    const Point3D pointOnBaseCircle = frame.origin.translated(radial * radius);

    const std::vector<Point3D> linePoints = sampling_utils::sampleFiniteLine(
        pointOnBaseCircle, frame.axisDirection.toVector(), frame.height,
        pointsPerGeneratrix);

    points.insert(points.end(), linePoints.begin(), linePoints.end());
  }

  return points;
}

std::vector<Point3D> sampleCylinderByAngle(const RevolutionFrame &frame,
                                           const Plane &plane, double radius,
                                           size_t pointCount) {
  std::vector<Point3D> points;

  if (pointCount == 0) {
    return points;
  }

  const double denominator = frame.axisDirection.dot(plane.getNormal());

  if (std::abs(denominator) < constants::ComputationTolerance) {
    return points;
  }

  points.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radial =
        sampling_utils::makeUnitRadialVector(frame.xDir, frame.yDir, theta);

    const Point3D pointOnBaseCircle = frame.origin.translated(radial * radius);

    const double numerator =
        Vector3D{plane.getOrigin(), pointOnBaseCircle}.dot(plane.getNormal());

    const double axial = -numerator / denominator;

    if (!sampling_utils::isInRange(axial, 0.0, frame.height)) {
      continue;
    }

    points.push_back(
        pointOnBaseCircle.translated(frame.axisDirection.toVector() * axial));
  }

  return points;
}

} // namespace

ConeIntersectionSampler::ConeIntersectionSampler(const Plane &plane,
                                                 const Cone &cone)
    : m_plane(plane), m_cone(cone) {
}

std::vector<Point3D> ConeIntersectionSampler::sample(size_t pointCount) const {
  std::vector<Point3D> points;

  if (pointCount == 0) {
    return points;
  }

  const Point3D apex = m_cone.getApex();
  const Point3D baseCenter = m_cone.getBaseCenter();
  const double radius = m_cone.getRadius();

  const RevolutionFrame frame = makeRevolutionFrame(apex, baseCenter);

  const double numerator =
      Vector3D{m_plane.getOrigin(), apex}.dot(m_plane.getNormal());

  if (std::abs(numerator) < constants::ComputationTolerance) {
    return sampleConePlaneThroughApex(frame, m_plane, radius, pointCount);
  }

  points.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radial =
        sampling_utils::makeUnitRadialVector(frame.xDir, frame.yDir, theta);

    const Vector3D generatrixDirection =
        frame.axisDirection.toVector() + radial * (radius / frame.height);

    const double denominator = generatrixDirection.dot(m_plane.getNormal());

    if (std::abs(denominator) < constants::ComputationTolerance) {
      continue;
    }

    const double axial = -numerator / denominator;

    if (!sampling_utils::isInRange(axial, 0.0, frame.height)) {
      continue;
    }

    const double currentRadius = radius * axial / frame.height;

    const Vector3D offset =
        frame.axisDirection.toVector() * axial + radial * currentRadius;

    points.push_back(apex.translated(offset));
  }

  return points;
}

CylinderIntersectionSampler::CylinderIntersectionSampler(
    const Plane &plane, const Cylinder &cylinder)
    : m_plane(plane), m_cylinder(cylinder) {
}

std::vector<Point3D>
CylinderIntersectionSampler::sample(size_t pointCount) const {
  if (pointCount == 0) {
    return {};
  }

  const Point3D firstBaseCenter = m_cylinder.getFirstBaseCenter();
  const Point3D secondBaseCenter = m_cylinder.getSecondBaseCenter();
  const double radius = m_cylinder.getRadius();

  const RevolutionFrame frame =
      makeRevolutionFrame(firstBaseCenter, secondBaseCenter);

  const double denominator = frame.axisDirection.dot(m_plane.getNormal());

  if (std::abs(denominator) >= constants::ComputationTolerance) {
    return sampleCylinderByAngle(frame, m_plane, radius, pointCount);
  }

  return sampleCylinderPlaneParallelToAxis(frame, m_plane, radius, pointCount);
}

IntersectionPointSampler::IntersectionPointSampler(
    std::unique_ptr<IIntersectionSampler> sampler)
    : m_sampler(std::move(sampler)) {
  if (!m_sampler) {
    throw std::invalid_argument("Intersection sampler must not be null.");
  }
}

std::vector<Point3D> IntersectionPointSampler::sample(size_t pointCount) const {
  return m_sampler->sample(pointCount);
}