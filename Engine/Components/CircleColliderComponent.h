#pragma once

#include "ColliderComponent.h"

namespace ChiefEngine {
	class CircleColliderComponent : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleColliderComponent)

		bool CheckCollision(const ColliderComponent& other) override;

		void Read(const JSON::value_t& value) override;

		/// <summary>
		/// Getter for protected value m_radius that describes the size of the hitbox
		/// </summary>
		/// <returns> m_radius member value</returns>
		inline float GetRadius() const { return m_radius; }
	protected:
		float m_radius = 0.0f;
	};
}
