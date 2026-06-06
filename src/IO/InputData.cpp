#include "IO/InputData.h"

#include <ostream>
#include <string>

namespace {

std::string shapeTypeToString(const ShapeType type) {
  switch (type) {
  case ShapeType::Cone:
    return "cone";

  case ShapeType::Cylinder:
    return "cylinder";
  }

  return "unknown";
}

} // namespace

void InputData::print(std::ostream &output) const {
  const auto printPoint = [&output](const Point3D &point) {
    output << '(' << point.getX() << ", " << point.getY() << ", "
           << point.getZ() << ')';
  };

  output << "Plane points:\n";
  printPoint(plane.firstPoint);
  output << '\n';

  printPoint(plane.secondPoint);
  output << '\n';

  printPoint(plane.thirdPoint);
  output << "\n\n";

  output << "Shape type: " << shapeTypeToString(shape.type) << '\n';

  output << "First point: ";
  printPoint(shape.firstPoint);
  output << '\n';

  output << "Second point: ";
  printPoint(shape.secondPoint);
  output << '\n';

  output << "Radius: " << shape.radius << '\n';
}