#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class ModelComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(ModelComponent)

		void Draw(const class Renderer& renderer) const override;
		void Read(const JSON::value_t& value) override;
	private:
	};
}