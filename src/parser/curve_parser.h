#pragma once
#ifndef CURVE_PARSER_H
#define CURVE_PARSER_H

#include <memory>
#include <vector>
#include <string>
#include "../curves/curve3d.h"
/**
 * @brief Parser for curve data files
 *
 * Handles reading and parsing of curve definitions from text files.
 * Supports three curve types: Circle (C), Ellipse (E), Helix (H).
 * Validates input data and reports errors for malformed lines.
 */
class CurveParser {
public:
    /**
     * @brief Parse curves from input file
     *
     * Reads the entire file, validates format, and creates curve objects.
     * File format:
     * - First line: number of curves
     * - Subsequent lines: curve definitions
     *
     * @param filename Path to input file
     * @return std::vector<std::unique_ptr<Curve3D>> Vector of parsed curves
     * @throws std::runtime_error If file cannot be opened or is malformed
     */
    static std::vector<std::unique_ptr<Curve3D>> parse_file(const std::string& filename);

private:
    /**
     * @brief Parse single line of curve definition
     *
     * Parses curve type, ID, name, coordinates, and type-specific parameters.
     * Creates appropriate Curve3D derived object.
     *
     * @param line Text line to parse
     * @return std::unique_ptr<Curve3D> Parsed curve object
     * @throws std::runtime_error If line format is invalid
     */
    static std::unique_ptr<Curve3D> parse_line(const std::string& line);

    /**
     * @brief Validate that radius is positive
     *
     * @param radius Radius value to validate
     * @return true if radius > 0.0
     * @return false otherwise
     */
    static bool validate_radius(double radius);

    /**
     * @brief Validate that both radii are positive
     *
     * @param r1 First radius
     * @param r2 Second radius
     * @return true if both radii > 0.0
     * @return false otherwise
     */
    static bool validate_radii(double r1, double r2);
};

#endif // CURVE_PARSER_H