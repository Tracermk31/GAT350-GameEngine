#include "pch.h"

#include "Engine.h"

#include <iostream>

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	/// <returns></returns>
	bool Engine::Initialize(float screenWidth, float screenHeight) {
		m_renderer.Initialize("Chief Engine", (short)screenWidth, (short)screenHeight);
		m_input.Initialize();
		m_time.Reset();
		m_audioSystem.Initialize();
		m_particleSystem.Initialize(5000);
		m_physics.Initialize();
		return true;
	};

	/// <summary>
	/// 
	/// </summary>
	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.ShutDown();
		m_audioSystem.Shutdown();
		m_particleSystem.Shutdown();
		m_physics.Shutdown();
	};

	/// <summary>
	/// 
	/// </summary>
	void Engine::Update() {
		m_input.Update();
		m_audioSystem.Update();
		m_time.Tick();
		m_particleSystem.Update(m_time.getDeltaTime());
		m_physics.Update(m_time.getDeltaTime());
	};
}
