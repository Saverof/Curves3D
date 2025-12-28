#pragma once
#ifndef CURVE3D_H
#define CURVE3D_H

#include "../../include/geometry/point3d.h"
#include <cstdint>
#include <string>
#include <memory>


/**
 * @brief Abstract base class for all 3D parametric curves
 *
 * Defines the interface that all concrete curve types must implement.
 * Each curve has unique ID and name for identification.
 * Uses pure virtual functions for parametric point and derivative calculation.
 */
class Curve3D {
public:
    /**
     * @brief Construct a new Curve3D object
     *
     * @param id Unique 64-bit identifier
     * @param name Text label for the curve
     */
    Curve3D(uint64_t id, const std::string& name)
        : id_(id), name_(name) {
    }

    virtual ~Curve3D() = default; // Virtual destructor for proper cleanup
    
    // Pure virtual methods that must be implemented by derived classes

    /**
     * @brief Calculate 3D point on curve at parameter t
     *
     * @param t Parameter along the curve (typically angle for circles/ellipses)
     * @return Point3D Coordinates of the point
     */
    virtual Point3D point(double t) const = 0;

    /**
     * @brief Calculate first derivative (3D vector) at parameter t
     *
     * @param t Parameter along the curve
     * @return Vector3D Derivative vector (tangent to the curve)
     */
    virtual Vector3D derivative(double t) const = 0;

    // Accessor methods
    uint64_t id() const { return id_; }
    const std::string& name() const { return name_; }

    /**
     * @brief Print formatted information about the curve at parameter t
     *
     * Displays ID, name, point coordinates and derivative vector.
     * Format is consistent for all curve types.
     *
     * @param t Parameter value for evaluation
     */
    virtual void print_info(double t) const;

private:
    uint64_t id_;
    std::string name_;
};

#endif // CURVE3D_H