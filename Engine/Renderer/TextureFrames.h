#pragma once

#include "Math/Rect.h"
#include "Math/Vector2.h"

#include "Renderer/Texture.h"

#include "Resources/ResourceManager.h"

#include <string>

namespace ChiefEngine {
	class TextureFrames : public Resource {
	private:
		unsigned short m_numberOfColumns = 0;
		unsigned short m_numberOfRows = 0;
		unsigned short m_startFrame = 0;
		unsigned short m_totalFrames = 0;

		Vector2 m_frameSize{ 0.0f };
		resource_t<Texture> m_texture;
	public:
		bool Load(const std::string& filename, class Renderer& renderer);
		Rect GetFrameRect(unsigned short frame);

		unsigned short GetTotalFrames() const { return m_totalFrames; }
		resource_t<Texture> GetTexture() { return m_texture; }
	};
}