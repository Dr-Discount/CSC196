#pragma once
#include "Math.h"
#include <cassert>

template<typename T>
struct Vector2 {
	T x, y;

	Vector2() = default;
	Vector2(T x, T y, T z) : x{ x }, y{ y } z { z } {}

	T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
	T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

	Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y, z + v.z); }
	Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y, z - v.z); }
	Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y, z * v.z); }
	Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y, z / v.z); }

	Vector2 operator + (float s) const { return Vector2(x + s, y + s, z + s); }
	Vector2 operator - (float s) const { return Vector2(x - s, y - s, z - s); }
	Vector2 operator * (float s) const { return Vector2(x * s, y * s, z * s); }
	Vector2 operator / (float s) const { return Vector2(x / s, y / s, z / s); }
	
	Vector2 operator += (const Vector2& v) { x += v.x; y += v.y, z += v.z; return *this; }
	Vector2 operator -= (const Vector2& v) { x -= v.x; y -= v.y, z -= v.z; return *this; }
	Vector2 operator *= (const Vector2& v) { x *= v.x; y *= v.y, z *= v.z; return *this; }
	Vector2 operator /= (const Vector2& v) { x /= v.x; y /= v.y, z /= v.z; return *this; }

	Vector2 operator += (float s) { x += s; y += s, z += s; return *this; }
	Vector2 operator -= (float s) { x -= s; y -= s, z -= s; return *this; }
	Vector2 operator *= (float s) { x *= s; y *= s, z *= s; return *this; }
	Vector2 operator /= (float s) { x /= s; y /= s, z /= s; return *this; }

	float LenghtSqr() { return x * x + y * y + z * z; }
	float Length() { return viper::math::sqrtf(LenghtSqr()); }
};

using ivec2 = Vector2<int>;
using vec2 = Vector2<float>;
