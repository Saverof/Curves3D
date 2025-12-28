#define _USE_MATH_DEFINES

#include "curve3d.h"
#include <iostream>
#include <iomanip>

void Curve3D::print_info(double t) const {
    std::cout << "ID: " << id_ << ", Name: " << name_ << "\n";
    std::cout << "Point: " << point(t) << "\n";
    std::cout << "Derivative: " << derivative(t) << "\n";
    std::cout << "------------------------\n";
}