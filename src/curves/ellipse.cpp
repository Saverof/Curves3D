#define _USE_MATH_DEFINES

#include "ellipse.h"
#include <cmath>
/**
 * @brief Ellipse constructor
 *
 * Note: Radii validation should be done by parser before object creation.
 * Both radii must be positive.
 */
Ellipse::Ellipse(uint64_t id, const std::string& name,
    double center_x, double center_y, double center_z,
    double radius_x, double radius_y)
    : Curve3D(id, name), radius_x_(radius_x), radius_y_(radius_y) {
    center_.x() = center_x;
    center_.y() = center_y;
    center_.z() = center_z;
}
/**
 * @brief Calculate point on ellipse at parameter t
 *
 * Parametric equation:
 *   x = center_x + radius_x * cos(t)
 *   y = center_y + radius_y * sin(t)
 *   z = center_z (constant, ellipse lies in XY plane)
 *
 * @param t Parameter (angle in radians)
 * @return Point3D Coordinates on the ellipse
 */
Point3D Ellipse::point(double t) const {
    Point3D p;
    p.x() = center_.x() + radius_x_ * std::cos(t);
    p.y() = center_.y() + radius_y_ * std::sin(t);
    p.z() = center_.z();  // Ellipse lies in XY plane
    return p;
}
/**
 * @brief Calculate derivative (tangent vector) at parameter t
 *
 * Derivative of parametric equation:
 *   dx/dt = -radius_x * sin(t)
 *   dy/dt = radius_y * cos(t)
 *   dz/dt = 0
 *
 * @param t Parameter (angle in radians)
 * @return Vector3D Tangent vector to the ellipse
 */
Vector3D Ellipse::derivative(double t) const {
    Vector3D d;
    d.x() = -radius_x_ * std::sin(t);
    d.y() = radius_y_ * std::cos(t);
    d.z() = 0.0; // No change in z direction
    return d;
}