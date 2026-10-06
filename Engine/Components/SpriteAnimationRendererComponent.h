#pragma once

#include "SpriteRendererComponent.h"

#include "Resources/ResourceManager.h"

namespace ChiefEngine {
	class SpriteAnimationRendererComponent : public SpriteRendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void Start() override;

		void Update(float dt) override;

		void Read(const JSON::value_t& value) override;
	private:
		unsigned short m_currentFrame;
		float m_framesPerSecond = 30.0f;
		bool m_looping = true;

		float m_frameTimer = 0;

		std::string m_textureFramesName;
		resource_t<class TextureFrames> m_textureFrames;
	};
}