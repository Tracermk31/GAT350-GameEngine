#pragma once

#include "CharacterBase.h"

class Damager : public CharacterBase {
public:
	CLASS_PROTOTYPE(Damager)

	void Read(const ChiefEngine::JSON::value_t& value) override;

	void SetDamage(short damage) { m_damage = damage; }
	short GetDamage() const { return m_damage; }
protected:
	short m_damage{ 1 };
};