#pragma once

#include "Texture.h"

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <vector>

namespace ChiefEngine {
	class Particle {
	public:
		bool active{ false };
		float lifespan{ 1 };
		float scale = 1.0f;

		Vector2 position{ 0.0f, 0.0f };
		Vector2 velocity{ 0.0f, 0.0f };
		Color color{ 0.0f, 0.0f, 0.0f };
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