#define _USE_MATH_DEFINES

#include "helix.h"
#include <cmath>
/**
 * @brief Helix constructor
 *
 * Note: Radius validation should be done by parser before object creation.
 * Radius must be positive, step can be any real number (positive, negative, or zero).
 */
Helix::Helix(uint64_t id, const std::string& name,
    double center_x, double center_y, double center_z,
    double radius, double step)
    : Curve3D(id, name), radius_(radius), step_(step) {
    center_.x() = center_x;
    center_.y() = center_y;
    center_.z() = center_z;
}
/**
 * @brief Calculate point on helix at parameter t
 *
 * Parametric equation:
 *   x = center_x + radius * cos(t)
 *   y = center_y + radius * sin(t)
 *   z = center_z + (step * t) / (2?)
 *
 * @param t Parameter (angle in radians)
 * @return Point3D Coordinates on the helix
 */
Point3D Helix::point(double t) const {
    Point3D p;
    p.x() = center_.x() + radius_ * std::cos(t);
    p.y() = center_.y() + radius_ * std::sin(t);
    p.z() = center_.z() + (step_ * t) / (2.0 * M_PI);
    return p;
}
/**
 * @brief Calculate derivative (tangent vector) at parameter t
 *
 * Derivative of parametric equation:
 *   dx/dt = -radius * sin(t)
 *   dy/dt = radius * cos(t)
 *   dz/dt = step / (2?)
 *
 * @param t Parameter (angle in radians)
 * @return Vector3D Tangent vector to the helix
 */
Vector3D Helix::derivative(double t) const {
    Vector3D d;
    d.x() = -radius_ * std::sin(t);
    d.y() = radius_ * std::cos(t);
    d.z() = step_ / (2.0 * M_PI); // Constant vertical rate
    return d;
}