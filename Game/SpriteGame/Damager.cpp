#include "Damager.h"

#include "Core/Factory.h"

FACTORY_REGISTER(Damager)

void Damager::Read(const ChiefEngine::JSON::value_t& value) {
	ChiefEngine::Actor::Read(value);

	JSON_READ_MEMBER(value, "damage", m_damage);
}