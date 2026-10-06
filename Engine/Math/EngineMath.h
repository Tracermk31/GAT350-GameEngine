#pragma once

namespace ChiefEngine {
	constexpr float PI = 3.1415926535897932384626433832795f;
	constexpr float TWO_PI = 6.283185307179586476925286766559f;
	constexpr float HALF_PI = 1.5707963267948966192313216916398f;

	constexpr float RADIAN_TO_DEGREE = 180.0f / PI;
	constexpr float DEGREE_TO_RADIAN = PI / 180.0f;

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns></returns>
	template<typename T>
	T Min(T value1, T value2) {
		return (value1 < value2) ? value1 : value2;
	}
	
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value1"></param>
	/// <param name="value2"></param>
	/// <returns></returns>
	template<typename T>
	T Max(T value1, T value2) {
		return (value1 > value2) ? value1 : value2;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <param name="value"></param>
	template<typename T>
	void Wrap(T min, T max, T& value) {
		if (value > max) value = min;
		if (value < min) value = max;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <param name="value"></param>
	template<typename T>
	void Clamp(T min, T max, T& value) {
		if (value >= max) value = max;
		if (value <= min) value = min;
	}
}