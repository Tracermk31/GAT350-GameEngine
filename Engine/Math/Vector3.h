#pragma once

#include <cmath>
#include <cassert>

namespace ChiefEngine {
	class Vector3 {
	public:
		union {
			struct { float x, y, z; };
			struct { float r, g, b; };
		};

		Vector3() = default;
		Vector3(float val) : x{ val }, y{ val }, z{ val } {}
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		float operator [] (unsigned int index) const { assert(index < 3); return (index == 0) ? x : (index == 1) ? y : z; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		float& operator [] (unsigned int index) { assert(index < 3); return (index == 0) ? x : (index == 1) ? y : z; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator == (const Vector3& other) const { return(this->x == other.x) && (this->y == other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator != (const Vector3& other) const { return(this->x != other.x) || (this->y != other.y); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float LengthSqr() const { return (x * x) + (y * y) + (z * z); }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float Length() const { return std::sqrt(LengthSqr()); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		float Dot(const Vector3& other) const { return (this->x * other.x) + (this->y * other.y) + (this->z * other.z); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Vector3 Normalized() const { return *this / Length(); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3 operator+(const Vector3& other) const { return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3 operator-(const Vector3& other) const { return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3 operator*(const Vector3& other) const { return Vector3(this->x * other.x, this->y * other.y, this->z * other.z); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3 operator/(const Vector3& other) const { return Vector3(this->x / other.x, this->y / other.y, this->z / other.z); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3 operator+(float val) const { return Vector3(this->x + val, this->y + val, this->z + val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3 operator-(float val) const { return Vector3(this->x - val, this->y - val, this->z - val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3 operator*(float val) const { return Vector3(this->x * val, this->y * val, this->z * val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3 operator/(float val) const { return Vector3(this->x / val, this->y / val, this->z / val); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3& operator+=(const Vector3& other) { this->x += other.x; this->y += other.y, this->z += other.z; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3& operator-=(const Vector3& other) { this->x -= other.x; this->y -= other.y, this->z -= other.z; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3& operator*=(const Vector3& other) { this->x *= other.x; this->y *= other.y, this->z *= other.z; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector3& operator/=(const Vector3& other) { this->x /= other.x; this->y /= other.y, this->z /= other.z; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3& operator+=(float val) { this->x += val; this->y += val, this->z += val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3& operator-=(float val) { this->x -= val; this->y -= val, this->z -= val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3& operator*=(float val) { this->x *= val; this->y *= val, this->z *= val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector3& operator/=(float val) { this->x /= val; this->y /= val, this->z /= val; return *this; }
	};

	using Color = Vector3;
}
