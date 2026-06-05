#include "IntersectionPointSampler.h"

#include "Common/Constants.h"
#include "SamplingUtils.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace {

class RevolutionFrame {
public:
  RevolutionFrame(const Point3D &origin, const Point3D &axisEnd)
      : m_origin(origin) {
    const Vector3D axis{origin, axisEnd};
    m_height = axis.getLength();

    if (m_height < constants::MinLength) {
      throw std::runtime_error(
          "Failed to create revolution frame: zero height.");
    }

    m_axisDirection = Direction3D{axis};
    m_xDir = sampling_utils::makePerpendicularDirection(m_axisDirection);
    m_yDir = m_axisDirection.cross(m_xDir);
  }

  Point3D getOrigin() const {
    return m_origin;
  }

  Direction3D getAxisDirection() const {
    return m_axisDirection;
  }

  Direction3D getXDir() const {
    return m_xDir;
  }

  Direction3D getYDir() const {
    return m_yDir;
  }

  double getHeight() const {
    return m_height;
  }

private:
  Point3D m_origin;
  Direction3D m_axisDirection;
  Direction3D m_xDir;
  Direction3D m_yDir;
  double m_height{0.0};
};

std::vector<double>
findConeGeneratrixAnglesInPlane(const RevolutionFrame &frame,
                                const Direction3D &planeNormal, double radius) {
  const double k = radius / frame.getHeight();

  const double a = frame.getAxisDirection().dot(planeNormal);
  const double b = k * frame.getXDir().dot(planeNormal);
  const double c = k * frame.getYDir().dot(planeNormal);

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
    points.push_back(frame.getOrigin());
    return points;
  }

  const size_t pointsPerGeneratrix =
      std::max<size_t>(2, pointCount / angles.size());

  points.reserve(pointsPerGeneratrix * angles.size());

  for (const double theta : angles) {
    const Vector3D radial = sampling_utils::makeUnitRadialVector(
        frame.getXDir(), frame.getYDir(), theta);

    for (size_t i = 0; i < pointsPerGeneratrix; ++i) {
      const double t =
          static_cast<double>(i) / static_cast<double>(pointsPerGeneratrix - 1);

      const double axial = frame.getHeight() * t;
      const double currentRadius = radius * axial / frame.getHeight();

      const Vector3D offset =
          frame.getAxisDirection().toVector() * axial + radial * currentRadius;

      points.push_back(frame.getOrigin().translated(offset));
    }
  }

  return points;
}

std::vector<double>
findCylinderGeneratrixAnglesInPlane(const RevolutionFrame &frame,
                                    const Plane &plane, double radius) {
  const double a =
      Vector3D{plane.getOrigin(), frame.getOrigin()}.dot(plane.getNormal());

  const double b = radius * frame.getXDir().dot(plane.getNormal());
  const double c = radius * frame.getYDir().dot(plane.getNormal());

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
    const Vector3D radial = sampling_utils::makeUnitRadialVector(
        frame.getXDir(), frame.getYDir(), theta);

    const Point3D pointOnBaseCircle =
        frame.getOrigin().translated(radial * radius);

    const std::vector<Point3D> linePoints = sampling_utils::sampleFiniteLine(
        pointOnBaseCircle, frame.getAxisDirection().toVector(),
        frame.getHeight(), pointsPerGeneratrix);

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

  const double denominator = frame.getAxisDirection().dot(plane.getNormal());

  if (std::abs(denominator) < constants::ComputationTolerance) {
    return points;
  }

  points.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radial = sampling_utils::makeUnitRadialVector(
        frame.getXDir(), frame.getYDir(), theta);

    const Point3D pointOnBaseCircle =
        frame.getOrigin().translated(radial * radius);

    const double numerator =
        Vector3D{plane.getOrigin(), pointOnBaseCircle}.dot(plane.getNormal());

    const double axial = -numerator / denominator;

    if (!sampling_utils::isInRange(axial, 0.0, frame.getHeight())) {
      continue;
    }

    points.push_back(pointOnBaseCircle.translated(
        frame.getAxisDirection().toVector() * axial));
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

  const RevolutionFrame frame{apex, baseCenter};

  const double numerator =
      Vector3D{m_plane.getOrigin(), apex}.dot(m_plane.getNormal());

  if (std::abs(numerator) < constants::ComputationTolerance) {
    return sampleConePlaneThroughApex(frame, m_plane, radius, pointCount);
  }

  points.reserve(pointCount);

  for (size_t i = 0; i < pointCount; ++i) {
    const double theta = 2.0 * constants::Pi * static_cast<double>(i) /
                         static_cast<double>(pointCount);

    const Vector3D radial = sampling_utils::makeUnitRadialVector(
        frame.getXDir(), frame.getYDir(), theta);

    const Vector3D generatrixDirection = frame.getAxisDirection().toVector() +
                                         radial * (radius / frame.getHeight());

    const double denominator = generatrixDirection.dot(m_plane.getNormal());

    if (std::abs(denominator) < constants::ComputationTolerance) {
      continue;
    }

    const double axial = -numerator / denominator;

    if (!sampling_utils::isInRange(axial, 0.0, frame.getHeight())) {
      continue;
    }

    const double currentRadius = radius * axial / frame.getHeight();

    const Vector3D offset =
        frame.getAxisDirection().toVector() * axial + radial * currentRadius;

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

  const RevolutionFrame frame{firstBaseCenter, secondBaseCenter};

  const double denominator = frame.getAxisDirection().dot(m_plane.getNormal());

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