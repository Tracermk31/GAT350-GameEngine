#pragma once

#include "RendererComponent.h"

#include "Resources/Resource.h"

namespace ChiefEngine {
	class ModelComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(ModelComponent)

		void Draw(const class Renderer& renderer) const override;
		void Read(const JSON::value_t& value) override;
	private:
		resource_t<class Model> m_model;
		std::vector<resource_t<class MaterialInstance>> m_materials;
	};
}