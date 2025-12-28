cmake_minimum_required(VERSION 3.15)
project(Curves3D VERSION 1.0.0 LANGUAGES CXX)

# C++ standard configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler extensions for portability


if(NOT DEFINED M_PI)
    add_compile_definitions(M_PI=3.14159265358979323846)
endif()

# Compiler warning settings
if(MSVC)
    # For MSVC: high warning level, treat all warnings as errors
    add_compile_options(/W4 /WX)
    
    # Disable some MSVC-specific warnings
    # 4251: 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
    # 4275: non-DLL-interface class used as base for DLL-interface class
    add_compile_options(/wd4251 /wd4275)
    
    # Enable multibyte encoding instead of Unicode for simplicity
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    # For GCC/Clang: all warnings, pedantic mode, warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    
    # Disable some specific warnings
    add_compile_options(-Wno-unused-parameter)  # Unused function parameters
endif()

# Output directory policy for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)

# Output directory policy for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files list
set(SOURCES
    src/main.cpp
    src/curves/curve3d.cpp
    src/curves/circle.cpp
    src/curves/ellipse.cpp
    src/curves/helix.cpp
    src/parser/curve_parser.cpp
)

# Create executable target
add_executable(curves3d ${SOURCES})

# Configure include directories
target_include_directories(curves3d PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Link required system libraries
if(UNIX AND NOT APPLE)
    # For Linux: link math library
    target_link_libraries(curves3d m)
endif()

# Add convenience target for running the program
add_custom_target(run 
    COMMAND curves3d ${CMAKE_SOURCE_DIR}/data/curves_to_check.txt
    DEPENDS curves3d
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running the program with curves_to_check.txt"
)

# Informational messages
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")