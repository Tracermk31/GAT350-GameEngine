#pragma once

#include "Box2DPhysicsComponent.h"
#include "Engine.h"

#include "Framework/Actor.h"

#include "Core/EngineStrings.h"
#include "Core/Factory.h"

#include "Math/EngineMath.h"

namespace ChiefEngine {
	//FACTORY_REGISTER(Box2DPhysicsComponent)

	Box2DPhysicsComponent::Box2DPhysicsComponent(const Box2DPhysicsComponent& other) {
		m_bodyDef = other.m_bodyDef;
		m_size = other.m_size;
		m_scale = other.m_scale;
	}

	void Box2DPhysicsComponent::Start() {
		m_bodyDef.actor = GetOwner();
		m_physicsBody = std::make_unique<PhysicsBody>(
			GetOwner()->GetTransform(),
			m_size,
			m_bodyDef,
			G_Engine().GetPhysics()
		);
	}

	void Box2DPhysicsComponent::Update(float dt) {
		GetOwner()->SetPosition(GetPosition());
		GetOwner()->SetRotation(GetRotation() * RADIAN_TO_DEGREE);
	}

	void Box2DPhysicsComponent::ApplyForce(const Vector2& force) {
		m_physicsBody->ApplyForce(force);
	}

	void Box2DPhysicsComponent::SetVelocity(const Vector2& velocity) {
		m_physicsBody->SetVelocity(velocity);
	}

	Vector2 Box2DPhysicsComponent::GetVelocity() const {
		return m_physicsBody->GetVelocity();
	}
	
	void Box2DPhysicsComponent::ApplyTorque(float torque) {
		m_physicsBody->ApplyTorque(torque);
	}

	void Box2DPhysicsComponent::SetAngularVelocity(float angularVelocity) {
		m_physicsBody->SetAngularVelocity(angularVelocity);
	}

	float Box2DPhysicsComponent::GetAngularVelocity() const {
		return m_physicsBody->GetAngularVelocity();
	}
	
	void Box2DPhysicsComponent::SetPosition(const Vector2& position) {
		m_physicsBody->SetPosition(position);
	}

	Vector2 Box2DPhysicsComponent::GetPosition() const {
		return m_physicsBody->GetPosition();
	}
	
	void Box2DPhysicsComponent::SetRotation(float rotation) {
		m_physicsBody->SetRotation(rotation);
	}

	float Box2DPhysicsComponent::GetRotation() const {
		return m_physicsBody->GetRotation();
	}

	void Box2DPhysicsComponent::Read(const JSON::value_t& value) {
		PhysicsComponent::Read(value);
		m_bodyDef.gravityScale = m_gravityScale;
		m_bodyDef.angularDamping = m_angularDamping;

		JSON_READ_MEMBER(value, "size", m_size);
		JSON_READ_MEMBER(value, "scale", m_scale);

		JSON_READ_MEMBER(value, "linearDamping", m_bodyDef.linearDamping);
		JSON_READ_MEMBER(value, "constrainAngle", m_bodyDef.constrainAngle);
		JSON_READ_MEMBER(value, "isDynamic", m_bodyDef.isDynamic);
		JSON_READ_MEMBER(value, "friction", m_bodyDef.friction);
		JSON_READ_MEMBER(value, "restitution", m_bodyDef.restitution);
		JSON_READ_MEMBER(value, "density", m_bodyDef.density);
		JSON_READ_MEMBER(value, "isSensor", m_bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_MEMBER(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (EqualsIgnoreCase(shapeName, "box")) m_bodyDef.shape = PhysicsBody::Shape::Box;
			else if (EqualsIgnoreCase(shapeName, "capsule")) m_bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (EqualsIgnoreCase(shapeName, "circle")) m_bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}
}