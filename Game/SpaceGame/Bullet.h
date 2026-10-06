#pragma once

#include "Framework/Scene.h"

class Bullet : public ChiefEngine::Actor {
public:
	Bullet() = default;

	CLASS_PROTOTYPE(Bullet)

	void Update(float dt, float maxX, float maxY) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="speed"></param>
	inline void SetSpeed(float speed) {
		m_speed = speed;
	}
private:
	float m_speed = 0.0f;
};