#include "CharacterBase.h"

void CharacterBase::Read(const ChiefEngine::JSON::value_t& value) {
	ChiefEngine::Actor::Read(value);

	JSON_READ_MEMBER(value, "health", m_health);
	JSON_READ_MEMBER(value, "speed", m_speed);
}