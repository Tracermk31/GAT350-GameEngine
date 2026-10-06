#pragma once

#include "SpriteAnimationRendererComponent.h"

#include "Resources/ResourceManager.h"

namespace ChiefEngine {
	class SpriteAnimatorRendererComponent : public SpriteRendererComponent {
	public:
		struct SpriteAnimation {
			std::string name;
			float framesPerSecond{ 30.0f };
			bool isLooping{ true };
			resource_t<class TextureFrames> textureFrames;
		};

		CLASS_PROTOTYPE(SpriteAnimatorRendererComponent)

		void Start() override;
		void Update(float dt) override;

		void Play(const std::string& name);

		void Read(const JSON::value_t& value) override;

		void Pause(bool isPaused = true) {
			m_pause = isPaused;
		}

		bool IsPaused() const {
			return m_pause;
		}

		unsigned short GetFrame() const { 
			return m_currentFrame; 
		}
		bool IsAnimationDone() const { 
			return m_currentFrame == m_spriteAnimation.textureFrames->GetTotalFrames() - 1; 
		}

		const std::string& GetAnimationName() const {
			return m_spriteAnimation.name;
		}
	private:
		unsigned short m_currentFrame = 0;
		float m_frameTimer = 0;
		bool m_pause = false;

		std::string m_defaultAnimationName;

		SpriteAnimation m_spriteAnimation;
		std::map<std::string, SpriteAnimation> m_spriteAnimations;
	};
}