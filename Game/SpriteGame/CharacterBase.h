#pragma once

#include "Framework/Actor.h"

class CharacterBase : public ChiefEngine::Actor {
public:
	enum class State {
		MOVE,
		PREPARE_ATTACK,
		ATTACK,
		HIT,
		DEATH
	};

	void Read(const ChiefEngine::JSON::value_t& value) override;

	float GetSpeed() const { return m_speed; }
	void SetSpeed(float speed) { m_speed = speed; }

	short GetHealth() const { return m_health; }
protected:
	State m_state = State::MOVE;
	float m_speed = 0.0f;
	float m_stateTimer = 0.0f;
	short m_health = 10;
};