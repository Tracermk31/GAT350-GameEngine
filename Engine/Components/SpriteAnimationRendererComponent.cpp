#include "pch.h"

#include "Engine.h"
#include "SpriteAnimationRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Start() {
		if (m_textureFramesName.empty()) {
			std::cerr << "Invalid data";
			return;
		}
		m_textureFrames = Resources().Get<TextureFrames>(m_textureFramesName, G_Engine().GetRenderer());
		if (!m_textureFrames) {
			std::cerr << "could not load data from " << m_textureFramesName << std::endl;
		} else {
			m_sourceRectangle = m_textureFrames->GetFrameRect(0);
			m_size = Vector2{ m_sourceRectangle.size.x, m_sourceRectangle.size.y };
			m_texture = m_textureFrames->GetTexture();
		}
	}

	void SpriteAnimationRendererComponent::Update(float dt) {
		m_frameTimer += dt;
		float frameTime = 1.0f/m_framesPerSecond;

		while (m_frameTimer >= frameTime) {
			m_currentFrame++;
			if (m_looping) {
				m_currentFrame %= m_textureFrames->GetTotalFrames();
			}
			else {
				if (m_currentFrame >= m_textureFrames->GetTotalFrames() - 1) {
					m_currentFrame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}

		m_sourceRectangle = m_textureFrames->GetFrameRect(m_currentFrame);
	}

	void SpriteAnimationRendererComponent::Read(const JSON::value_t& value) {
		SpriteRendererComponent::Read(value);

		JSON_READ_MEMBER_REQUIRED(value, "framesPerSecond", m_framesPerSecond);
		JSON_READ_MEMBER(value, "looping", m_looping);

		JSON_READ_MEMBER_REQUIRED(value, "textureFrames", m_textureFramesName);
	}
}