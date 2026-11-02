#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class CameraComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(CameraComponent)

		void Draw(const class Renderer& renderer) const override;

	private:
	};
}
