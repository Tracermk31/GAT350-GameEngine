#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class MaterialComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(MaterialComponent)

		void Draw(const class Renderer& renderer) const override;
		void Read(const JSON::value_t& value) override;
	private:
	};
}
