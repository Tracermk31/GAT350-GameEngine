#include "pch.h"

#include "Renderer.h"
#include "ParticleSystem.h"

#include "Resources/ResourceManager.h"

namespace ChiefEngine{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="poolSize"></param>
	/// <returns></returns>
	bool ParticleSystem::Initialize(size_t poolSize) {
		m_particles.resize(poolSize);
		return true;
	}

	/// <summary>
	/// 
	/// </summary>
	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (!particle.active) { 
				continue; 
			}

			particle.lifespan -= dt;

			if (particle.lifespan > 0) {
				particle.position += (particle.velocity * dt);
			} else {
				particle.active = false;
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void ParticleSystem::Draw(Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				if (particle.particleTexture) {
					renderer.DrawTexture(*particle.particleTexture, particle.position.x, particle.position.y, 0.0f, particle.scale);
				} else {
					renderer.SetColorVector(particle.color);
					renderer.DrawPoint(particle.position.x, particle.position.y);
				}
			}
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="particle"></param>
	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle;
			freeParticle->active = true;
		}
	}

	void ParticleSystem::AddParticleAsTexture(const Particle& particle, const std::string& particleTexturePath, Renderer& renderer) {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle;
			freeParticle->active = true;
			freeParticle->particleTexture = Resources().Get<Texture>(particleTexturePath, renderer);
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}

		return nullptr;
	}
}