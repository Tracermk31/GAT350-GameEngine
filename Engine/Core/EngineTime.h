#pragma once

#include <cstdint>

namespace ChiefEngine {
	class Time {
	public:
		Time();

		void Reset();
		void Tick();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float getTime() const { return TicksToSeconds(m_currentTicks - m_startTicks); }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float getDeltaTime() const { return TicksToSeconds(m_deltaTicks) * m_timeScale; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="ticks"></param>
		/// <returns></returns>
		float TicksToSeconds(uint64_t ticks) const { return ticks / 1'000'000'000.0f; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="timeScale"></param>
		void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		float getTimeScale() const { return m_timeScale; }
	private:
		float m_timeScale = 1.0f;

		uint64_t m_startTicks = 0;
		uint64_t m_currentTicks = 0;
		uint64_t m_frameTicks = 0;
		uint64_t m_deltaTicks = 0;
	};
}