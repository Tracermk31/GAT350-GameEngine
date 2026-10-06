#pragma once

#include <random>
#include <cstdlib>

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline std::mt19937& Generator() {
		static std::random_device randomDevice;
		static std::mt19937 generator(randomDevice());

		return generator;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="seed"></param>
	inline void SeedRandom(unsigned int seed) {
		Generator().seed(seed);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline int RandomInt() {
		static std::uniform_int_distribution<> dist;
		return dist(Generator());
	}

	/// <summary>
	/// Get random integer value [0, max)
	/// </summary>
	/// <param name="max">exclusive max</param>
	/// <returns> Random integer between 0 and max (exclusive)</returns>
	inline int RandomInt(int max) {
		std::uniform_int_distribution<> dist(0, max - 1);
		return dist(Generator());
	}

	/// <summary>
	/// Get random integer value [min, max)
	/// </summary>
	/// <param name="min">inclusive min</param>
	/// <param name="max">exclusive max</param>
	/// <returns> Random integer between min (inclusive) and max (exclusive)</returns>
	inline int RandomInt(int min, int max) {
		if (min > max) {
			std::swap(min, max);
		}

		std::uniform_int_distribution<> dist(min, max - 1);
		return dist(Generator());
	}

	/// <summary>
	/// Get random number [0, 1]
	/// </summary>
	/// <returns> A number between 0 - 1</returns>
	inline float RandomFloat() {
		static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(Generator());
	}


	/// <summary>
	/// Get random number [0, max]
	/// </summary>
	/// <param name="max"> Inclusive maximum possible value</param>
	/// <returns> Random number between 0 and max (inclusive)</returns>
	inline float RandomFloat(float max) {
		std::uniform_real_distribution<float> dist(0.0f, max);
		return dist(Generator());
	}

	/// <summary>
	/// Get random number [min, max]
	/// </summary>
	/// <param name="min"> Inclusive minimum possible value</param>
	/// <param name="max"> Inclusive maximum possible value</param>
	/// <returns> Random number between min (inclusive) and max (inclusive) </returns>
	inline float RandomFloat(float min, float max) {
		if (min > max) {
			std::swap(min, max);
		}

		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline bool RandomBool() {
		std::bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}
}