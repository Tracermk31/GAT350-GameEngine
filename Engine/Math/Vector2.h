#pragma once

#include <cmath>
#include <cassert>

namespace ChiefEngine {
	class Vector2 {
	public:
		float x, y;

		Vector2() = default;
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ (float)x}, y{(float)y} {}
		Vector2(float x, int y) : x{ x}, y{(float)y} {}
		Vector2(int x, float y) : x{ (float)x}, y{ y} {}
		Vector2(unsigned int x, unsigned int y) : x{ static_cast<float>(x)}, y{static_cast<float>(y)} {}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		float operator [] (unsigned int index) const { assert(index < 2); return (index == 0) ? x : y; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		float& operator [] (unsigned int index) { assert(index < 2); return (index == 0) ? x : y; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator == (const Vector2& other) const { return(this->x == other.x) && (this->y == other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator != (const Vector2& other) const { return(this->x != other.x) || (this->y != other.y); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float GetX() const { return this->x; }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float GetY() const { return this->y; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float LengthSqr() const { return (x * x) + (y * y); }
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
		float Distance(const Vector2& other) const { return (other - *this).Length(); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		float Dot(const Vector2& other) const { return (this->x * other.x) + (this->y * other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		float AngleBetween(const Vector2& other) const { return std::acos(Dot(other)); }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float Angle() const { return std::atan2(this->y, this->x); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="radians"></param>
		/// <returns></returns>
		Vector2 Rotate(float radians) const {
			Vector2 temp = { 0.0f };
			temp.x = this->x * std::cos(radians) - this->y * std::sin(radians);
			temp.y = this->x * std::sin(radians) + this->y * std::cos(radians);
			return temp;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Vector2 Normalized() const { return *this/Length(); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2 operator+(const Vector2& other) const { return Vector2(this->x + other.x, this->y + other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2 operator-(const Vector2& other) const { return Vector2(this->x - other.x, this->y - other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2 operator*(const Vector2& other) const { return Vector2(this->x * other.x, this->y * other.y); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2 operator/(const Vector2& other) const { return Vector2(this->x / other.x, this->y / other.y); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2 operator+(float val) const { return Vector2(this->x + val, this->y + val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2 operator-(float val) const { return Vector2(this->x - val, this->y - val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2 operator*(float val) const { return Vector2(this->x * val, this->y * val); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2 operator/(float val) const { return Vector2(this->x / val, this->y / val); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2& operator+=(const Vector2& other) { this->x += other.x; this->y += other.y; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2& operator-=(const Vector2& other) { this->x -= other.x; this->y -= other.y; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2& operator*=(const Vector2& other) { this->x *= other.x; this->y *= other.y; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vector2& operator/=(const Vector2& other) { this->x /= other.x; this->y /= other.y; return *this; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2& operator+=(float val) { this->x += val; this->y += val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2& operator-=(float val) { this->x -= val; this->y -= val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2& operator*=(float val) { this->x *= val; this->y *= val; return *this; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="val"></param>
		/// <returns></returns>
		Vector2& operator/=(float val) { this->x /= val; this->y /= val; return *this; }
	};
}