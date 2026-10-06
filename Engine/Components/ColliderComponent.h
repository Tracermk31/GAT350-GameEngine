#pragma once

#include "Component.h"

namespace ChiefEngine {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(const ColliderComponent& other) = 0;
	};
}