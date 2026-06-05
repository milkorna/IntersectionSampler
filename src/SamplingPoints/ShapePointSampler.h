#pragma once

#include <cstddef>
#include <utility>

#include "Common/Cone.h"
#include "Common/Cylinder.h"
#include "Common/Point3D.h"

struct CylinderSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray bottomBasePoints;
  Point3DArray topBasePoints;
};

struct ConeSample {
  std::pair<Point3D, Point3D> axis;
  Point3DArray basePoints;
  Point3DArray generatrixPoints;
  Point3D apex;
};

template <typename Shape> struct ShapeSampleTraits;

template <> struct ShapeSampleTraits<Cylinder> {
  using Sample = CylinderSample;

  static Sample sample(const Cylinder &cylinder, std::size_t pointCount);
};

template <> struct ShapeSampleTraits<Cone> {
  using Sample = ConeSample;

  static Sample sample(const Cone &cone, std::size_t pointCount);
};

template <typename Shape> class ShapePointSampler {
public:
  using Sample = typename ShapeSampleTraits<Shape>::Sample;

  explicit ShapePointSampler(const Shape &shape) : m_shape(shape) {
  }

  Sample sample(std::size_t pointCount) const {
    return ShapeSampleTraits<Shape>::sample(m_shape, pointCount);
  }

private:
  Shape m_shape;
};

using CylinderPointSampler = ShapePointSampler<Cylinder>;
using ConePointSampler = ShapePointSampler<Cone>;