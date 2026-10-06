#include "pch.h"

#include "Engine.h"

#include "Texture.h"
#include "TextureFrames.h"

#include "Serialization/JSON.h"

namespace ChiefEngine {
	bool TextureFrames::Load(const std::string& filename, Renderer& renderer) {
		JSON::document_t document;

		if (!JSON::Load(filename, document)) {
			std::cerr << "Could not load Texture Frames from file: " << filename << std::endl;
			return false;
		}

		std::string textureName;
		JSON_READ_MEMBER_REQUIRED(document, "textureName", textureName);

		if (textureName.empty()) {
			std::cerr << "Could not read Texture Frames from document\n";
			return false;
		}

		m_texture = Resources().Get<Texture>(textureName, renderer);

		if (!m_texture) {
			std::cerr << "Unable to retrieve texture information from: " << textureName << std::endl;
			return false;
		}

		JSON_READ_MEMBER(document, "columns", m_numberOfColumns);
		JSON_READ_MEMBER(document, "rows", m_numberOfRows);
		JSON_READ_MEMBER(document, "startFrame", m_startFrame);
		JSON_READ_MEMBER(document, "totalFrames", m_totalFrames);

		if (m_numberOfColumns <= 0 || m_numberOfRows <= 0) {
			std::cerr << "Number of Columns or Rows equals zero\n";
			return false;
		}

		Vector2 textureSize = m_texture->GetSize();
		m_frameSize = textureSize / Vector2{ (m_numberOfColumns), (m_numberOfRows) };

		return true;
	}

	Rect TextureFrames::GetFrameRect(unsigned short frame) {
		if (frame >= m_totalFrames) {
			std::cerr << "Provided frame value is outside of the animations scope\n";
			frame = 0;
		}

		short currentFrame = m_startFrame + frame;
		short column = currentFrame % m_numberOfColumns;
		short row = currentFrame / m_numberOfColumns;
		float x = column * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect(x, y, m_frameSize.x, m_frameSize.y);
	}
}

