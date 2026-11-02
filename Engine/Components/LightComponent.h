#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class LightComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(LightComponent)

		void Draw(const class Renderer& renderer) const override;

	private:
	};
}
