#pragma once

#include "PhysicsComponent.h"

namespace ChiefEngine {
	class RigidBodyPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(RigidBodyPhysicsComponent)

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

		void Update(float dt);
		void Read(const JSON::value_t& value) override;
	private:
		Vector2 m_acceleration{ 0.0f };
		float m_angularAcceleration{ 0.0f };

		Vector2 m_velocity{ 0.0f };
		float m_angularVelocity{ 0.0f };
	};
}