#pragma once

#include "Framework/Scene.h"

class Enemy : public ChiefEngine::Actor {
public:
	Enemy() = default;

	CLASS_PROTOTYPE(Enemy)

	void Update(float dt, float maxX, float maxY) override;
	void OnCollision(Actor* other) override;

	void Read(const ChiefEngine::JSON::value_t& value) override;
private:
	short m_pointValue = 0;
	float m_shootDelay = 0;
	float m_speed = 0.0f;
};