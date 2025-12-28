#include "curve_parser.h"
#include "../curves/circle.h"
#include "../curves/ellipse.h"
#include "../curves/helix.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <charconv>
#include <string_view>

using namespace std;
/**
 * @brief Main file parsing function
 *
 * Implements the complete file parsing pipeline:
 * 1. Open file and check accessibility
 * 2. Read curve count from first line
 * 3. Parse each curve line
 * 4. Handle errors gracefully with warnings
 * 5. Return vector of valid curves
 */
vector<unique_ptr<Curve3D>> CurveParser::parse_file(const string& filename) {
    vector<unique_ptr<Curve3D>> curves;

    // Open input file
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    // Read number of curves
    if (!getline(file, line)) {
        throw runtime_error("Empty file");
    }

    int num_curves = 0;
    try {
        num_curves = stoi(line);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("Invalid number of curves: ") + line + " (" + e.what() + ")"
        );
    }

    if (num_curves <= 0) {
        throw runtime_error("Number of curves must be positive");
    }

    // Pre-allocate memory for efficiency with large files
    curves.reserve(num_curves);

    int line_num = 1; // First line was the count
    while (getline(file, line)) {
        line_num++;

        if (line.empty()) continue;

        try {
            auto curve = parse_line(line);
            if (curve) {
                curves.push_back(move(curve));
            }
        }
        catch (const exception& e) {
            // Report error but continue parsing (skip malformed lines)
            cerr << "Warning: Skipping line " << line_num
                << " - " << e.what() << endl;
        }
    }

    // Warn if parsed count doesn't match expected count
    if (curves.size() != static_cast<size_t>(num_curves)) {
        cerr << "Warning: Expected " << num_curves
            << " curves, but parsed " << curves.size() << endl;
    }

    return curves;
}

/**
 * @brief Parse individual curve definition line
 *
 * Line format examples:
 *   C 11100 "wheel_flange" 0.0 2.15 1.65 6.23
 *   E 22200 "cover_plate" 4.55 0.0 -1.0 2.0 3.0
 *   H 33300 "bolt_thread" -2.0 1.0 5.0 8.975 4.256
 *
 * Uses stringstream for simple tokenization.
 * For production code, consider more efficient parsing methods.
 */
unique_ptr<Curve3D> CurveParser::parse_line(const string& line) {
    istringstream iss(line);
    string type_str;

    // Read curve type tag (single character)
    if (!(iss >> type_str)) {
        throw runtime_error("Empty line");
    }

    char type = type_str[0];
    if (type_str.length() != 1) {
        throw runtime_error("Invalid curve type: " + type_str);
    }

    // Read curve ID (64-bit unsigned)
    uint64_t id;
    if (!(iss >> id)) {
        throw runtime_error("Invalid ID");
    }

    // Read curve name (enclosed in quotes)
    string name;
    iss >> ws; // Skip whitespace
    if (iss.peek() != '"') {
        throw runtime_error("Name must start with quotes");
    }

    // Read quoted name
    char quote;
    iss >> quote; // Read opening quote
    getline(iss, name, '"'); // Read until closing quote

    // Read center coordinates
    double cx, cy, cz;
    if (!(iss >> cx >> cy >> cz)) {
        throw runtime_error("Invalid center coordinates");
    }

    // Parse type-specific parameters and create appropriate curve object
    switch (type) {
    case 'C': {
        double radius;
        if (!(iss >> radius)) {
            throw runtime_error("Invalid radius for circle");
        }
        if (!validate_radius(radius)) {
            throw runtime_error("Circle radius must be positive");
        }
        return make_unique<Circle>(id, name, cx, cy, cz, radius);
    }

    case 'E': {
        double rx, ry;
        if (!(iss >> rx >> ry)) {
            throw runtime_error("Invalid radii for ellipse");
        }
        if (!validate_radii(rx, ry)) {
            throw runtime_error("Ellipse radii must be positive");
        }
        return make_unique<Ellipse>(id, name, cx, cy, cz, rx, ry);
    }

    case 'H': {
        double radius, step;
        if (!(iss >> radius >> step)) {
            throw runtime_error("Invalid radius or step for helix");
        }
        if (!validate_radius(radius)) {
            throw runtime_error("Helix radius must be positive");
        }
        // Step can be any real number, including negative
        return make_unique<Helix>(id, name, cx, cy, cz, radius, step);
    }

    default:
        throw runtime_error("Unknown curve type: " + string(1, type));
    }
}

/**
 * @brief Validate that a radius is positive
 *
 * Used for circles and helix radius validation.
 * Physical curves require positive radii.
 */
bool CurveParser::validate_radius(double radius) {
    return radius > 0.0;
}

/**
 * @brief Validate that both radii are positive
 *
 * Used for ellipse validation.
 */
bool CurveParser::validate_radii(double r1, double r2) {
    return r1 > 0.0 && r2 > 0.0;
}