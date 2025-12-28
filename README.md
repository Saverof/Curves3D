# Curves3D: A C++ Geometric Curves Hierarchy Implementation

**Curves3D** is a C++ program that implements a hierarchy of 3D geometric curves (circles, ellipses, and helixes). The program reads curve definitions from a file, stores them in a container, and performs various operations such as computing points and derivatives, filtering circles, sorting by radius, and summing radii. The project demonstrates object-oriented design, STL usage, and RAII principles.

## Features
### 3D Curve Types
- **Circle**: Defined by radius and center, parallel to the XY plane.
- **Ellipse**: Defined by two radii (along X and Y axes) and center, parallel to the XY plane.
- **Helix**: Spatial curve defined by radius, step, and center.

### Operations
- **Point and Derivative Calculation**: For each curve, compute the 3D point and first derivative at a given parameter t.
- **File Parsing**: Read curve definitions from a text file with a specified format.
- **Circle Filtering**: Create a second container that shares (via pointers) only the circles from the first container.
- **Sorting**: Sort the circles in ascending order of their radii.
- **Summation**: Compute the total sum of radii of all circles.

### Code Quality
- **RAII**: Automatic memory management using std::unique_ptr.
- **STL**: Extensive use of the C++ Standard Template Library (containers, algorithms, smart pointers).
- **Error Handling**: Comprehensive error checking and reporting.
- **Cross-Platform**: Compatible with Windows, Linux, and macOS.

### Requirements
- **C++17** compatible compiler (gcc, clang, MSVC)
- **CMake** 3.15 or higher

## Building the Project
### Using CMake
1. Clone and prepare
   ```bash
   git clone https://github.com/yourusername/3DCurvesHierarchy.git
   cd 3DCurvesHierarchy
   ```
2. Create a directory and generate build files
   ```bash
   cmake -S . -B build -G "Ninja"
   ```
3. Build and test the project
   ```bash
   cmake --build build --target run
   ```
4. Otherwise, use other input data
   ```bash
   ./build/bin/curves3d.exe ./data/additional_curves_1.txt
   ```
## Output
### Example input
```text
3
C 11100 "wheel_flange" 0.000000 2.150000 1.650000 6.230000
E 22200 "cover_plate" 4.550000 0.000000 -1.000000 2.000000 3.000000
H 33300 "bolt_thread" -2.000000 1.000000 5.000000 8.975000 4.256000
```
### Example output
```text
=== Parsed 3 curves ===

=== All curves at t = PI/4 (0.785398) ===
ID: 11100, Name: wheel_flange
Point: (4.405275, 6.555275, 1.650000)
Derivative: (-4.405275, 4.405275, 0.000000)
------------------------
ID: 22200, Name: cover_plate
Point: (5.964214, 2.121320, -1.000000)
Derivative: (-1.414214, 2.121320, 0.000000)
------------------------
ID: 33300, Name: bolt_thread
Point: (4.346283, 7.346283, 5.532000)
Derivative: (-6.346283, 6.346283, 0.677363)
------------------------

=== Found 1 circles ===

=== Sorted circles (by radius) ===
Circle ID: 11100, Name: wheel_flange, Radius: 6.230000

=== Statistics ===
Total number of curves: 3
Number of circles: 1
Sum of circle radii: 6.230000
```
### Example input curves_to_check
```text
9
C 111000111 "wheel_flange" 0.000000 0.000000 0.000000 1.000000
E 222000111 "access_hatch" 0.000000 0.000000 0.000000 2.000000 3.000000
H 333000111 "screw_thread" 0.000000 0.000000 0.000000 2.000000 6.283185
C 444000111 "pitch_sign" -10.000000 -20.000000 30.128000 5.000000
E 555000111 "cover_plate" -2.000000 5.000000 -10.896000 1.000000 4.000000
H 666000111 "nut_thread" 4.500000 -2.800000 10.000000 3.000000 4.000000
C 777000111 "centering_boss" 3.000000 4.000000 -2.000000 -2.000000
E 888000111 "cam_profile" 1.000000 -2.500000 5.000000 -10.000000 2.350000
H 999000111 "bolt_thread" 1.200000 5.600000 -7.000000 -4.550000 2.200000

```
### Example output for curves_to_check
```text
Warning: Skipping line 8 - Circle radius must be positive
Warning: Skipping line 9 - Ellipse radii must be positive
Warning: Skipping line 10 - Helix radius must be positive
Warning: Expected 9 curves, but parsed 6
=== Parsed 6 curves ===

=== All curves at t = PI/4 (0.785398) ===
ID: 111000111, Name: wheel_flange
Point: (0.707107, 0.707107, 0.000000)
Derivative: (-0.707107, 0.707107, 0.000000)
------------------------
ID: 222000111, Name: access_hatch
Point: (1.414214, 2.121320, 0.000000)
Derivative: (-1.414214, 2.121320, 0.000000)
------------------------
ID: 333000111, Name: screw_thread
Point: (1.414214, 1.414214, 0.785398)
Derivative: (-1.414214, 1.414214, 1.000000)
------------------------
ID: 444000111, Name: pitch_sign
Point: (-6.464466, -16.464466, 30.128000)
Derivative: (-3.535534, 3.535534, 0.000000)
------------------------
ID: 555000111, Name: cover_plate
Point: (-1.292893, 7.828427, -10.896000)
Derivative: (-0.707107, 2.828427, 0.000000)
------------------------
ID: 666000111, Name: nut_thread
Point: (6.621320, -0.678680, 10.500000)
Derivative: (-2.121320, 2.121320, 0.636620)
------------------------

=== Found 2 circles ===

=== Sorted circles (by radius) ===
Circle ID: 111000111, Name: wheel_flange, Radius: 1.000000
Circle ID: 444000111, Name: pitch_sign, Radius: 5.000000

=== Statistics ===
Total number of curves: 6
Number of circles: 2
Sum of circle radii: 6.000000
```
### Note on Warning Messages
The warnings shown in the output example (e.g., "Circle radius must be positive") demonstrate the program's error handling capabilities. Invalid curves are skipped with appropriate warning messages, while valid curves continue to be processed normally.

### The program will output:
- For each curve (at t = π/4):
- ID and name
- 3D point coordinates
- First derivative (3D vector)
### Statistics:
- Total number of curves
- Number of circles
- Sum of circle radii
### Testing
The project includes several test files in the data/ directory:
- curves_to_check.txt - Primary test file
- additional_curves_1.txt - Additional test data
- additional_curves_2.txt - additional_curves_3.txt - More test cases
### Project Structure
  ```text
  Curves3D/
  ├── CMakeLists.txt          # CMake build configuration
  ├── include/
  │   └── geometry/
  │       └── point3d.h       # 3D point/vector structure
  ├── data/...                # Data for verification
  ├── src/
  │   ├── main.cpp            # Main program
  │   ├── curves/             # Curve class hierarchy
  │   │   ├── curve3d.h/cpp   # Base class
  │   │   ├── circle.h/cpp    # Circle class
  │   │   ├── ellipse.h/cpp   # Ellipse class
  │   │   └── helix.h/cpp     # Helix class
  │   └── parser/
  │       ├── curve_parser.h  # File parser declaration
  │       └── curve_parser.cpp # File parser implementation
  └── README.md               # This file
  ```

## Implementation Details
### Parametric Equations
1. Circle (XY plane):
  - Point: ```C(t) = center + radius * (cos(t), sin(t), 0) ```
  - Derivative: ```C'(t) = radius * (-sin(t), cos(t), 0)```
2. Ellipse (XY plane):
  - Point: ```C(t) = center + (rx * cos(t), ry * sin(t), 0)```
  - Derivative: ```C'(t) = (-rx * sin(t), ry * cos(t), 0)```
3. Helix:
 - Point: ```C(t) = center + (radius * cos(t), radius * sin(t), step * t / (2π))```
 - Derivative: ```C'(t) = (-radius * sin(t), radius * cos(t), step / (2π))```

## License
This project is licensed under the MIT License - see the LICENSE file for details
