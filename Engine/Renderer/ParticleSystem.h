#pragma once

#include "Texture.h"

#include <vector>

namespace ChiefEngine {
	class Particle {
	public:
		bool active{ false };
		float lifespan{ 1 };
		float scale = 1.0f;

		glm::vec2 position{ 0.0f, 0.0f };
		glm::vec2 velocity{ 0.0f, 0.0f };
		glm::vec3 color{ 0.0f, 0.0f, 0.0f };
		resource_t<Texture> particleTexture;
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize(size_t poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);
		void AddParticleAsTexture(const Particle& particle, const std::string& particleTexturePath, Renderer& renderer);

	private:
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};
}