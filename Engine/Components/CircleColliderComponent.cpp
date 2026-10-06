#include "pch.h"

#include "Framework/Actor.h"
#include "Core/Factory.h"
#include "CircleColliderComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(CircleColliderComponent)

	/// <summary>
	/// Functions that checks whether two CircleColliderComponents have collided. 
	/// </summary>
	/// <param name="other">Other ColliderComponent to check collision against</param>
	/// <returns>True if collided, false if not</returns>
	bool CircleColliderComponent::CheckCollision(const ColliderComponent& other) {
		const CircleColliderComponent* circleCollider = dynamic_cast<const CircleColliderComponent*>(&other);
		if (!circleCollider) {
			return false;
		}
		return (GetOwner()->GetTransform().position.Distance(other.GetOwner()->GetTransform().position) <= (m_radius + circleCollider->GetRadius()));
	}

	/// <summary>
	/// Reads radius values from a provided JSON file
	/// </summary>
	/// <param name="value">JSON value to be read from</param>
	void CircleColliderComponent::Read(const JSON::value_t& value) {
		ColliderComponent::Read(value);

		JSON_READ_MEMBER(value, "radius", m_radius);
	}
}