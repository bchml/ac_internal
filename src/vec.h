#pragma once
#include <cmath>

struct Vec3 {
    float x, y, z;

    // Constructor
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Addition
    Vec3 operator+(const Vec3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    // Subtraction
    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    // Scalar division
    Vec3 operator/(float scalar) const {
        return { x / scalar, y / scalar, z / scalar };
    }

    // Scalar multiplication
    Vec3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }

    float Distance(const Vec3& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};