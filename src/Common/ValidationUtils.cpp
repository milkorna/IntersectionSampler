#include "ValidationUtils.h"

#include <stdexcept>

#include "Common/Constants.h"

namespace geometry_validation {

void validateRadius(double radius) {
  if (radius <= constants::MinLength) {
    throw std::invalid_argument("Radius must be positive.");
  }
}

void validateDifferentPoints(const Point3D &first, const Point3D &second,
                             const std::string_view message) {
  if (first.isEqual(second, constants::PointTolerance)) {
    throw std::invalid_argument(std::string{message});
  }
}

} // namespace geometry_validation