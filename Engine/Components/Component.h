#pragma once

#include "Framework/Object.h"

namespace ChiefEngine {
	class Actor;

	class Component : public Object {
	public:
		CLASS_PROTOTYPE(Component)

		Component() = default;
		virtual ~Component() = default;

		/// <summary>
		/// Getter for the m_owner member variable. This is a pointer to the Actor that owns the Component.
		/// </summary>
		/// <returns> m_owner member value</returns>
		inline Actor* GetOwner() const {
			return m_owner;
		}

		/// <summary>
		/// Setter for the m_owner member variable. This describes the Actor that has the Component.
		/// </summary>
		/// <param name="owner">a pointer to be set as the m_owner member value</param>
		inline void SetOwner(Actor* owner) { m_owner = owner; }

		virtual void Start() {}
		virtual void OnDestroy() {}

		virtual void Update(float dt) {}
	protected:
		Actor* m_owner = nullptr;
	};
}