#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>
#include "curves/curve3d.h"
#include "curves/circle.h"
#include "parser/curve_parser.h"


using namespace std;

/**
 * @brief Main program entry point
 *
 * Command line usage: curves3d <input_file>
 *
 * Program workflow:
 * 1. Parse command line arguments
 * 2. Load curves from input file
 * 3. Print information for all curves at t = ?/4
 * 4. Extract circles from all curves
 * 5. Sort circles by radius (ascending)
 * 6. Calculate sum of circle radii
 * 7. Display statistics
 */
int main(int argc, char* argv[]) {
    // Set output precision
    cout << fixed << setprecision(6);

    // Check command line arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        cerr << "Example: " << argv[0] << " curves_to_check.txt" << endl;
        return 1;
    }

    string filename = argv[1];

    try {
        // ==== STEP 1: Parse curves from file
        auto all_curves = CurveParser::parse_file(filename);

        cout << "=== Parsed " << all_curves.size() << " curves ===\n\n";

        // ==== STEP 2: Print all curves at t = ?/4 
        const double t = M_PI / 4.0; // Evaluation parameter as specified in requirements
        cout << "=== All curves at t = PI/4 (" << t << ") ===\n";
        for (const auto& curve : all_curves) {
            curve->print_info(t);
        }

        // ==== STEP 3: Extract circles only 
        // Create second container with raw pointers to circles (sharing, not cloning)
        vector<Curve3D*> circles;
        for (const auto& curve : all_curves) {
            if (auto* circle = dynamic_cast<Circle*>(curve.get())) {
                circles.push_back(circle);
            }
        }

        cout << "\n=== Found " << circles.size() << " circles ===\n";

        // ==== STEP 4: Sort circles by radius (ascending) 
        // Sort using lambda comparator that extracts radius from Circle objects
        sort(circles.begin(), circles.end(),
            [](Curve3D* a, Curve3D* b) {
                auto* circle_a = dynamic_cast<Circle*>(a);
                auto* circle_b = dynamic_cast<Circle*>(b);
                return circle_a->radius() < circle_b->radius();
            });

        // Optional: Display sorted circles (helpful for debugging)
        cout << "\n=== Sorted circles (by radius) ===\n";
        for (const auto& circle_ptr : circles) {
            auto* circle = dynamic_cast<Circle*>(circle_ptr);
            cout << "Circle ID: " << circle->id()
                << ", Name: " << circle->name()
                << ", Radius: " << circle->radius() << endl;
        }

        // ==== STEP 5: Compute total sum of circle radii
        // Use std::accumulate with lambda to sum radii
        double total_radius = accumulate(circles.begin(), circles.end(), 0.0,
            [](double sum, Curve3D* curve) {
                auto* circle = dynamic_cast<Circle*>(curve);
                return sum + circle->radius();
            });

        cout << "\n=== Statistics ===\n";
        cout << "Total number of curves: " << all_curves.size() << endl;
        cout << "Number of circles: " << circles.size() << endl;
        cout << "Sum of circle radii: " << total_radius << endl;

        // Memory management note:
        // - all_curves contains unique_ptr which automatically deletes objects
        // - circles contains raw pointers that don't own the objects
        // - All memory is cleaned up when all_curves goes out of scope
    }
    catch (const exception& e) {
        // Catch and report any runtime errors
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}