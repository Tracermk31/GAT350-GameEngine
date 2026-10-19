#pragma once

#include "Resources/Resource.h"

#include <string>

struct SDL_Texture;

namespace ChiefEngine {

	class Renderer;

	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const glm::vec2 GetSize() const { return m_size; }
		void SetSize();

		friend Renderer;
	private:
		SDL_Texture* m_texture{ nullptr };
		glm::vec2 m_size{ 0.0f, 0.0f };
	};
}