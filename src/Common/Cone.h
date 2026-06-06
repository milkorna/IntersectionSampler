#pragma once

#include "IO/InputData.h"

/**
 * @brief Represents a right circular cone
 */
class Cone {
public:
  /**
   * @brief Creates a cone from shape data parsed from the input file
   *
   * @param[in] inputData Parsed shape input data
   */
  explicit Cone(const ShapeInputData &inputData);

  /**
   * @brief Creates a cone from base center, apex and radius
   *
   * @param[in] baseCenter Center point of the cone base
   * @param[in] apex Apex point of the cone
   * @param[in] radius Radius of the cone base
   */
  explicit Cone(const Point3D &baseCenter, const Point3D &apex,
                const double radius);

  /**
   * @brief Gets the center point of the cone base
   *
   * @return Base center point
   */
  Point3D getBaseCenter() const;

  /**
   * @brief Gets the apex point of the cone
   *
   * @return Apex point
   */
  Point3D getApex() const;

  /**
   * @brief Gets the radius of the cone base
   *
   * @return Base radius
   */
  double getRadius() const;

private:
  Point3D m_baseCenter;
  Point3D m_apex;
  double m_radius{0.0};
};