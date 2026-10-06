#include "Bullet.h"

#include "Core/Factory.h"

#include "Math/EngineMath.h"

#include "Components/PhysicsComponent.h"

using namespace ChiefEngine;

FACTORY_REGISTER(Bullet)

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void Bullet::Update(float dt, float maxX, float maxY) {
	auto physicsComponent = GetComponent<PhysicsComponent>();
	if (physicsComponent) {
		Vector2 forward{ 1.0f, 0.0f };
		Vector2 force = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * m_speed;

		physicsComponent->SetVelocity(force);

		Vector2 position = physicsComponent->GetPosition();
		Clamp(0.0f, maxX, position.x);
		Clamp(0.0f, maxY, position.y);
		physicsComponent->SetPosition(position);
	}

	Actor::Update(dt, maxX, maxY);

	Clamp(0.0f, maxX, m_transform.position.x);
	Clamp(0.0f, maxY, m_transform.position.y);

	if (m_transform.position.x >= maxX || m_transform.position.x <= 0.0f || m_transform.position.y >= maxY || m_transform.position.y <= 0.0f) {
		BeDestroyed();
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="value"></param>
void Bullet::Read(const JSON::value_t& value) {
	Actor::Read(value);

	JSON_READ_MEMBER(value, "speed", m_speed);
}