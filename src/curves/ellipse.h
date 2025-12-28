#pragma once
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "curve3d.h"
/**
 * @brief Ellipse curve in 3D space (parallel to XY plane)
 *
 * Parametric formula: C(t) = center + (rx * cos(t), ry * sin(t), 0)
 * Derivative: C'(t) = (-rx * sin(t), ry * cos(t), 0)
 * Ellipse has two distinct radii: major and minor axes along X and Y.
 */
class Ellipse : public Curve3D {
public:
    /**
     * @brief Construct a new Ellipse object
     *
     * @param id Unique identifier
     * @param name Text label
     * @param center_x X coordinate of center
     * @param center_y Y coordinate of center
     * @param center_z Z coordinate of center
     * @param radius_x Radius along X axis (must be positive)
     * @param radius_y Radius along Y axis (must be positive)
     */
    Ellipse(uint64_t id, const std::string& name,
        double center_x, double center_y, double center_z,
        double radius_x, double radius_y);

    // Override pure virtual functions from Curve3D
    Point3D point(double t) const override;
    Vector3D derivative(double t) const override;

    // Accessor methods specific to Ellipse
    double radius_x() const { return radius_x_; }
    double radius_y() const { return radius_y_; }
    const Point3D& center() const { return center_; }

private:
    Point3D center_;
    double radius_x_;
    double radius_y_;
};

#endif // ELLIPSE_H