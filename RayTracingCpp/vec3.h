#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

struct vec3 {
	double x, y, z;

	vec3() : x(0), y(0), z(0) {}

	vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	inline vec3 operator+(const vec3& other) const {
		return vec3{ x + other.x, y + other.y, z + other.z };
	}

	inline vec3 operator-(const vec3& other) const {
		return vec3{ x - other.x, y - other.y, z - other.z };
	}

	inline vec3 operator*(double other) const {
		return vec3(x * other, y * other, z * other);
	}

	inline vec3 operator/(double other) const {
		return *this * (1 / other);
	}

	inline double magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	inline vec3 normalize() const {
		return *this / this->magnitude();
	}

};

// Allows reversed inputs (scalar * vec3 instead of vec3 * scalar)
inline vec3 operator*(double other, const vec3& v) {
	return v * other;
}

inline double dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 cross(const vec3& a, const vec3& b) {
	return vec3{ a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x };
}

#endif
