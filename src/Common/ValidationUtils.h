#pragma once

#include "Point3D.h"
#include <string_view>

namespace geometry_validation {

void validateRadius(double radius);

void validateDifferentPoints(const Point3D &first, const Point3D &second,
                             const std::string_view message);

} // namespace geometry_validation