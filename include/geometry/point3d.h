#pragma once
#ifndef POINT3D_H
#define POINT3D_H

#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>


/**
 * @brief 3D point structure with x, y, z coordinates
 *
 * Uses std::array for storage to enable efficient memory layout and
 * standard library compatibility. Also defines Vector3D as an alias
 * since both points and vectors share the same mathematical structure.
 */
struct Point3D {
    std::array<double, 3> data{ 0.0, 0.0, 0.0 };

    // Accessor methods for better readability
    double x() const { return data[0]; }
    double y() const { return data[1]; }
    double z() const { return data[2]; }

    double& x() { return data[0]; }
    double& y() { return data[1]; }
    double& z() { return data[2]; }

    /**
     * @brief Output stream operator for formatted point display
     * 
     * Displays point coordinates with 6 decimal places precision
     * in format: (x, y, z)
     */
    friend std::ostream& operator<<(std::ostream& os, const Point3D& p) {
        os << std::fixed << std::setprecision(6)
            << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")";
        return os;
    }
};

// Alias for 3D vector - mathematically identical to Point3D but semantically different
using Vector3D = Point3D;

#endif // POINT3D_H