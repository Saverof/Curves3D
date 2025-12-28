#pragma once
#ifndef HELIX_H
#define HELIX_H

#include "curve3d.h"
/**
 * @brief 3D Helix (spiral) curve
 *
 * Parametric formula: C(t) = center + (radius * cos(t), radius * sin(t), step * t / (2?))
 * Derivative: C'(t) = (-radius * sin(t), radius * cos(t), step / (2?))
 * One full revolution (2? in parameter space) increases Z coordinate by step value.
 */
class Helix : public Curve3D {
public:
    /**
     * @brief Construct a new Helix object
     *
     * @param id Unique identifier
     * @param name Text label
     * @param center_x X coordinate of center
     * @param center_y Y coordinate of center
     * @param center_z Z coordinate of center (starting point)
     * @param radius Helix radius (must be positive)
     * @param step Vertical displacement per full revolution (can be any real number)
     */
    Helix(uint64_t id, const std::string& name,
        double center_x, double center_y, double center_z,
        double radius, double step);

    // Override pure virtual functions from Curve3D
    Point3D point(double t) const override;
    Vector3D derivative(double t) const override;

    // Accessor methods specific to Helix
    double radius() const { return radius_; }
    double step() const { return step_; }
    const Point3D& center() const { return center_; }

private:
    Point3D center_;
    double radius_;
    double step_;
};

#endif // HELIX_H