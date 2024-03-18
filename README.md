# Vector Math Library

This is a simple C++ library for vector mathematics, providing classes for 2D and 3D vectors.

## Introduction

The Vector Math Library (Vectormath) consists of two main classes: Vec2D for 2D vectors and Vec3D for 3D vectors. These classes offer functionality for basic vector operations and support different coordinate systems including Cartesian, polar, spherical, and cylindrical coordinates.

## Coordinate Systems

The library allows you to work with different coordinate systems by defining the desired standard coordinate system using preprocessor directives. Available coordinate systems are:

- Cartesian 3D (CARTESIAN_IS_3D_STANDARD)
- Cartesian 2D (CARTESIAN_IS_2D_STANDARD)
- Polar (POLAR_IS_STANDARD)
- Spherical (SPHERE_IS_STANDARD)
- Cylindrical (CYLINDER_IS_STANDARD)

You can define which coordinate system to use by uncommenting the corresponding preprocessor directive in the header file.

## Classes

### Vec2D

The Vec2D class represents a 2D vector. It provides methods for basic vector operations and supports both Cartesian and polar coordinate systems.

#### Constructors

- Vec2D(float X, float Y): Constructs a 2D vector in Cartesian coordinates with the given X and Y components.
- Vec2D(float radius, float angle): Constructs a 2D vector in polar coordinates with the given radius and angle.

#### Methods

- length(): Calculates the length of the vector.
- dotProduct(Vec2D Mathvector): Calculates the dot product of this vector with another vector.
- calcAngle(Vec2D Mathvector): Calculates the angle between this vector and another vector.
- polarSystemArea(): Calculates the area of a circle in polar coordinates.
- polarSystemCircumference(): Calculates the circumference of a circle in polar coordinates.
- Getters and setters for vector components.

### Vec3D

The Vec3D class extends Vec2D to represent 3D vectors. It provides additional methods for vector operations in 3D space and supports Cartesian, spherical, and cylindrical coordinate systems.

#### Constructors

- Vec3D(float X, float Y, float Z): Constructs a 3D vector in Cartesian coordinates with the given X, Y, and Z components.
- Vec3D(float radius, float phi, float theta): Constructs a 3D vector in spherical coordinates with the given radius, phi, and theta.
- Vec3D(float radius, float phi, float height): Constructs a 3D vector in cylindrical coordinates with the given radius, phi, and height.

#### Methods

- Methods inherited from Vec2D.
- Additional methods for vector operations in 3D space.
- Methods to convert between different coordinate systems.
- Volumes and surfaces of sphere and cylinder systems.

## Usage

To use the library, include the header file Vectormath.h and define the desired standard coordinate system. Then, create instances of Vec2D or Vec3D vectors and perform vector operations as needed.

cpp
#include "Vectormath.h"

int main() {
    // Example usage of Vec2D and Vec3D
    // ...
    return 0;
}
