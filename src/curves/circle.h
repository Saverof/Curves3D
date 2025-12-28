#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include "curve3d.h"

/**
 * @brief Circle curve in 3D space (parallel to XY plane)
 *
 * Parametric formula: C(t) = center + radius * (cos(t), sin(t), 0)
 * Derivative: C'(t) = radius * (-sin(t), cos(t), 0)
 * All circles are parallel to the XY plane with constant Z coordinate.
 */
class Circle : public Curve3D {
public:
    /**
     * @brief Construct a new Circle object
     *
     * @param id Unique identifier
     * @param name Text label
     * @param center_x X coordinate of center
     * @param center_y Y coordinate of center
     * @param center_z Z coordinate of center (constant for all points)
     * @param radius Circle radius (must be positive)
     */
    Circle(uint64_t id, const std::string& name,
        double center_x, double center_y, double center_z,
        double radius);

    // Override pure virtual functions from Curve3D
    Point3D point(double t) const override;
    Vector3D derivative(double t) const override;

    // Accessor methods specific to Circle
    double radius() const { return radius_; }
    const Point3D& center() const { return center_; }

private:
    Point3D center_;
    double radius_;
};

#endif // CIRCLE_H