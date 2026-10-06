#pragma once

#include "PhysicsComponent.h"

#include "Physics/PhysicsBody.h"

namespace ChiefEngine {
	class Box2DPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(Box2DPhysicsComponent)

		Box2DPhysicsComponent() = default;
		Box2DPhysicsComponent(const Box2DPhysicsComponent& other);

		void Start() override;
		void Update(float dt) override;
		
		virtual void ApplyForce(const Vector2& force) override;
		virtual void SetVelocity(const Vector2& velocity) override;
		virtual Vector2 GetVelocity() const override;

		virtual void ApplyTorque(float torque) override;
		virtual void SetAngularVelocity(float angularVelocity) override;
		virtual float GetAngularVelocity() const override;

		virtual void SetPosition(const Vector2& position) override;
		virtual Vector2 GetPosition() const override;

		virtual void SetRotation(float rotation) override;
		virtual float GetRotation() const override;

		virtual void Read(const JSON::value_t& value) override;
	private:
		Vector2 m_size{ 1 };
		Vector2 m_scale{ 1 };

		PhysicsBody::PhysicsBodyDef m_bodyDef;
		std::unique_ptr<PhysicsBody> m_physicsBody;
	};
}