#pragma once

#include "IO/InputData.h"

/**
 * @brief Represents a right circular cylinder
 */
class Cylinder {
public:
  /**
   * @brief Creates a cylinder from shape data parsed from the input file
   *
   * @param[in] inputData Parsed shape input data
   */
  explicit Cylinder(const ShapeInputData &inputData);

  /**
   * @brief Creates a cylinder from base centers and radius
   *
   * @param[in] firstBaseCenter Center point of the first cylinder base
   * @param[in] secondBaseCenter Center point of the second cylinder base
   * @param[in] radius Radius of the cylinder bases
   */
  explicit Cylinder(const Point3D &firstBaseCenter,
                    const Point3D &secondBaseCenter, const double radius);

  /**
   * @brief Gets the center point of the first cylinder base
   *
   * @return First base center point
   */
  Point3D getFirstBaseCenter() const;

  /**
   * @brief Gets the center point of the second cylinder base
   *
   * @return Second base center point
   */
  Point3D getSecondBaseCenter() const;

  /**
   * @brief Gets the radius of the cylinder bases
   *
   * @return Base radius
   */
  double getRadius() const;

private:
  Point3D m_firstBaseCenter;
  Point3D m_secondBaseCenter;
  double m_radius{0.0};
};