#include "pch.h"

#include "Font.h"

namespace ChiefEngine {
	Font::~Font() {
		if (m_ttfFont != nullptr) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <param name="fontSize"></param>
	/// <returns></returns>
	bool Font::Load(const std::string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			std::cerr << "Could not load font: " << name << std::endl;
			return false;
		}

		return true;
	}
}