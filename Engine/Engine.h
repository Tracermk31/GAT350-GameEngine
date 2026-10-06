#pragma once

#include "Audio/Audio.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"

#include "Input/Input.h"

#include "Core/File.h"
#include "Core/Random.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Core/EngineTime.h"
#include "Core/EngineStrings.h"

#include "Components/Box2DPhysicsComponent.h"
#include "Components/TilemapRendererComponent.h"

#include "Math/EngineMath.h"

#include "Physics/Physics.h"

#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Renderer/Tilemap.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/TextureFrames.h"

#include "Resources/ResourceManager.h"

#include "Serialization/JSON.h"

#include <vector>
#include <fmod.hpp>
#include <iostream>

namespace ChiefEngine {
	class Engine : public Singleton<Engine> {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize(float screenWidth, float screenHeight);
		void Shutdown();

		void Update();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Time& GetTime() { return m_time; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Input& GetInput() { return m_input; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Renderer& GetRenderer() { return m_renderer; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Audio& GetAudio() { return m_audioSystem; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ParticleSystem& GetParticleSystem() { return m_particleSystem; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Physics& GetPhysics() { return m_physics; }
	private:
		ParticleSystem m_particleSystem;
		Time m_time;
		Input m_input;
		Renderer m_renderer;
		Audio m_audioSystem;
		Physics m_physics;
	};

	inline Engine& G_Engine() { return Engine::Instance(); }
}