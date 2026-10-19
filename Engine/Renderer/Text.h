#pragma once

#include "Font.h"

struct SDL_Texture;

namespace ChiefEngine {
	class Renderer;

	class Text {
	public:
		Text() = default;
		Text(resource_t<Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const glm::vec3& color);
		void Draw(Renderer& renderer, float x, float y) const;

	private:
		resource_t<Font> m_font;
		SDL_Texture* m_texture{ nullptr };
	};

}
