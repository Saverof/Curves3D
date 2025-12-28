#define _USE_MATH_DEFINES

#include "circle.h"
#include <cmath>

/**
 * @brief Circle constructor with parameter validation
 *
 * Note: Radius validation should be done by parser before object creation.
 * This constructor assumes valid positive radius.
 */
Circle::Circle(uint64_t id, const std::string& name,
    double center_x, double center_y, double center_z,
    double radius)
    : Curve3D(id, name), radius_(radius) {
    // Initialize center coordinates
    center_.x() = center_x;
    center_.y() = center_y;
    center_.z() = center_z;
}
/**
 * @brief Calculate point on circle at parameter t
 *
 * Parametric equation:
 *   x = center_x + radius * cos(t)
 *   y = center_y + radius * sin(t)
 *   z = center_z (constant, circle lies in XY plane)
 *
 * @param t Parameter (angle in radians)
 * @return Point3D Coordinates on the circle
 */
Point3D Circle::point(double t) const {
    Point3D p;
    p.x() = center_.x() + radius_ * std::cos(t);
    p.y() = center_.y() + radius_ * std::sin(t);
    p.z() = center_.z();  // Circle lies in XY plane, z is constant
    return p;
}

/**
 * @brief Calculate derivative (tangent vector) at parameter t
 *
 * Derivative of parametric equation:
 *   dx/dt = -radius * sin(t)
 *   dy/dt = radius * cos(t)
 *   dz/dt = 0
 *
 * @param t Parameter (angle in radians)
 * @return Vector3D Tangent vector to the circle
 */
Vector3D Circle::derivative(double t) const {
    Vector3D d;
    d.x() = -radius_ * std::sin(t);
    d.y() = radius_ * std::cos(t);
    d.z() = 0.0;
    return d;
}