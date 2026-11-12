#include "pch.h"

#include "Engine.h"
#include "ModelComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(ModelComponent)

	void ModelComponent::Draw(const Renderer& renderer) const {
		ObjectUniform objectUniform{
			.model = m_owner->GetTransform().GetMatrix(),
			.normalMatrix = m_owner->GetTransform().GetMatrix()
		};

		renderer.SetVertexUniform(UniformSlot::OBJECT, &objectUniform, sizeof(objectUniform));
		renderer.SetFragmentUniform(UniformSlot::OBJECT, &objectUniform, sizeof(objectUniform));

		m_model->Draw(renderer, m_materials);
	}

	void ModelComponent::Read(const JSON::value_t& value) {
		RendererComponent::Read(value);

		std::string modelName;
		JSON_READ_MEMBER(value, "model", modelName);

		m_model = Resources().Get<Model>(modelName, G_Engine().GetRenderer());

		// "materials": [ "materials/brick.instance.json", null ] - one entry per slot, null keeps the model's material
		if (JSON_HAS_BY_DATA(value, "materials")) {
			for (const auto& entry : JSON_GET_BY_DATA(value, "materials").GetArray()) {
				if (entry.IsString()) {
					std::string entryString = entry.GetString();
					auto material = Resources().Get<MaterialInstance>(entryString, G_Engine().GetRenderer());
					if (!material) std::cerr << "Could not load material: " << entry.GetString() << std::endl;
					m_materials.push_back(material);
				}
				else {
					m_materials.push_back(nullptr);
				}
			}
		}

	}
}