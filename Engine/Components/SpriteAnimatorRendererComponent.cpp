#include "pch.h"

#include "Engine.h"
#include "SpriteAnimatorRendererComponent.h"

#include "Core/Factory.h"
#include "Core/EngineStrings.h"

#include "Renderer/TextureFrames.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteAnimatorRendererComponent)

	void SpriteAnimatorRendererComponent::Start() {
		if (!m_defaultAnimationName.empty()) {
			Play(m_defaultAnimationName);
		} else {
			Play(m_spriteAnimations.begin()->first);
		}
	}

	void SpriteAnimatorRendererComponent::Update(float dt) {
		if (!m_spriteAnimation.textureFrames) {
			return;
		}

		m_frameTimer += dt;
		float frameTime = 1.0f / m_spriteAnimation.framesPerSecond;

		while (m_frameTimer >= frameTime) {
			m_currentFrame++;
			if (m_spriteAnimation.isLooping) {
				m_currentFrame %= m_spriteAnimation.textureFrames->GetTotalFrames();
			}
			else {
				if (m_currentFrame >= m_spriteAnimation.textureFrames->GetTotalFrames() - 1) {
					m_currentFrame = m_spriteAnimation.textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}

		m_sourceRectangle = m_spriteAnimation.textureFrames->GetFrameRect(m_currentFrame);
	}

	void SpriteAnimatorRendererComponent::Play(const std::string& name) {
		if (EqualsIgnoreCase(name, m_spriteAnimation.name)) {
			return;
		}

		auto iterator = m_spriteAnimations.find(ToLower(name));
		if (iterator == m_spriteAnimations.end()) {
			std::cerr << "Could not find animation: " << name << std::endl;
		}

		m_spriteAnimation = iterator->second;

		m_currentFrame = 0;
		m_frameTimer = 0.0f;

		m_texture = m_spriteAnimation.textureFrames->GetTexture();
		m_sourceRectangle = m_spriteAnimation.textureFrames->GetFrameRect(m_currentFrame);
	}

	void SpriteAnimatorRendererComponent::Read(const JSON::value_t& value) {
		SpriteRendererComponent::Read(value);

		JSON_READ_MEMBER(value, "defaultAnimation", m_defaultAnimationName);

		if (JSON_HAS_BY_DATA(value, animations) && JSON_GET_BY_DATA(value, animations).IsArray()) {
			for (auto& animatorValue : JSON_GET_BY_DATA(value, animations).GetArray()) {
				SpriteAnimation spriteAnimation;

				std::string textureAnimationName;

				JSON_READ_MEMBER(animatorValue, "name", spriteAnimation.name);

				std::string textureFrames;
				JSON_READ_BY_DATA_REQUIRED(animatorValue, textureFrames);

				if (!textureFrames.empty())
				{
					spriteAnimation.textureFrames = Resources().Get<TextureFrames>(textureFrames, G_Engine().GetRenderer());
					if (!spriteAnimation.textureFrames)
					{
						std::cerr << "Could not load texture frames: " << textureFrames << std::endl;
					}
				}

				JSON_READ_MEMBER_REQUIRED(animatorValue, "framesPerSecond", spriteAnimation.framesPerSecond);
				JSON_READ_MEMBER(animatorValue, "looping", spriteAnimation.isLooping);

				m_spriteAnimations[ToLower(spriteAnimation.name)] = spriteAnimation;
			}
		}
	}
}
