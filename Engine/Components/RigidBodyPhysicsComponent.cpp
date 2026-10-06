#include "pch.h"

#include "Core/Factory.h"

#include "Framework/Actor.h"

#include "RigidBodyPhysicsComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(RigidBodyPhysicsComponent)

	void RigidBodyPhysicsComponent::ApplyForce(const Vector2& force) {
		m_acceleration += force / m_mass;
	}

	void RigidBodyPhysicsComponent::SetVelocity(const Vector2& velocity) {
		m_velocity = velocity;
	}

	Vector2 RigidBodyPhysicsComponent::GetVelocity() const {
		return m_velocity;
	}

	void RigidBodyPhysicsComponent::ApplyTorque(float torque) {
		m_angularAcceleration += torque / m_mass;
	}

	void RigidBodyPhysicsComponent::SetAngularVelocity(float angularVelocity) {
		m_angularVelocity = angularVelocity;
	}

	float RigidBodyPhysicsComponent::GetAngularVelocity() const {
		return m_angularVelocity;
	}

	void RigidBodyPhysicsComponent::SetPosition(const Vector2& position) {
		GetOwner()->SetPosition(position);
	}

	Vector2 RigidBodyPhysicsComponent::GetPosition() const {
		return GetOwner()->GetTransform().position;
	}

	void RigidBodyPhysicsComponent::SetRotation(float rotation) {
		GetOwner()->SetPosition(rotation);
	}

	float RigidBodyPhysicsComponent::GetRotation() const {
		return GetOwner()->GetTransform().rotation;
	}

	void RigidBodyPhysicsComponent::Update(float dt) {
		m_velocity += m_acceleration * dt;
		m_velocity *= (1.0f / (1.0f + (m_damping * dt)));

		m_angularVelocity += m_angularAcceleration * dt;
		m_angularVelocity *= (1.0f / (1.0f + (m_angularDamping * dt)));

		SetPosition(GetPosition() += m_velocity * dt);
		GetOwner()->SetPosition(GetPosition());

		float rotation = GetOwner()->GetTransform().rotation;
		rotation += m_angularVelocity * dt;
		GetOwner()->SetRotation(rotation);

		m_acceleration = { 0.0f };
		m_angularAcceleration = 0.0f;
	}

	void RigidBodyPhysicsComponent::Read(const JSON::value_t& value) {
		PhysicsComponent::Read(value);

		JSON_READ_MEMBER(value, "velocity", m_velocity);
		JSON_READ_MEMBER(value, "angularVelocity", m_angularVelocity);
	}
}