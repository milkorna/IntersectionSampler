#pragma once

#include "Direction3D.h"
#include "Point3D.h"

struct PlaneInputData;

/**
 * @brief Represents a plane in 3D space
 */
class Plane {
public:
  /**
   * @brief Creates a plane from data parsed from the input file
   *
   * @param[in] inputData Parsed plane input data
   */
  explicit Plane(const PlaneInputData &inputData);

  /**
   * @brief Creates a plane from origin, normal and reference direction
   *
   * @param[in] origin Plane origin point
   * @param[in] normal Plane normal direction
   * @param[in] refDir Reference direction on the plane
   */
  explicit Plane(const Point3D &origin, const Direction3D &normal,
                 const Direction3D &refDir);

  /**
   * @brief Gets the plane origin
   *
   * @return Plane origin point
   */
  Point3D getOrigin() const;

  /**
   * @brief Gets the plane normal
   *
   * @return Plane normal direction
   */
  Direction3D getNormal() const;

  /**
   * @brief Gets the reference direction on the plane
   *
   * @return Plane reference direction
   */
  Direction3D getRefDir() const;

private:
  Point3D m_origin;
  Direction3D m_normal;
  Direction3D m_refDir;
};