#include "pch.h"

#include "EngineTime.h"

namespace ChiefEngine {
	Time::Time() {
		Reset();
	};

	/// <summary>
	/// 
	/// </summary>
	void Time::Reset() {
		m_startTicks = SDL_GetTicksNS();
		m_frameTicks = SDL_GetTicksNS();
		m_currentTicks = SDL_GetTicksNS();
	}

	/// <summary>
	/// 
	/// </summary>
	void Time::Tick() {
		m_currentTicks = SDL_GetTicksNS();
		m_deltaTicks = m_currentTicks - m_frameTicks;
		m_frameTicks = m_currentTicks;
	}
}