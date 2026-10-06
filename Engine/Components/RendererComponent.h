#pragma once

#include "Component.h"

namespace ChiefEngine {
	class RendererComponent : public Component {
	public:
		virtual void Draw(const class Renderer& renderer) const = 0;
	};
}


