#pragma once

#include <iostream>

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="stringToLower"></param>
	/// <returns></returns>
	inline std::string ToLower(const std::string& stringToLower) {
		std::string lowerString = stringToLower;

		for (auto& character : lowerString) {
			character = std::tolower(character);
		}
		return lowerString;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="stringToUpper"></param>
	/// <returns></returns>
	inline std::string ToUpper(const std::string& stringToUpper) {
		std::string upperString = stringToUpper;

		for (auto& character : upperString) {
			character = std::toupper(character);
		}
		return upperString;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="thisString"></param>
	/// <param name="otherString"></param>
	/// <returns></returns>
	inline bool EqualsIgnoreCase(const std::string& thisString, const std::string& otherString) {
		if (thisString.size() != otherString.size()) { 
			return false; 
		} else {
			return (ToLower(thisString) == ToLower(otherString));
		}
	}
}