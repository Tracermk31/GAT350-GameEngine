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
		if (value.HasMember("materials")) {
			for (const auto& entry : JSON_GET_BY_NAME(value, "materials").GetArray()) {
				if (entry.IsString()) {
					auto material = Resources().Get<MaterialInstance>(entry.GetString(), G_Engine().GetRenderer());
					if (!material) std::cerr << "Could not load material: " << entry.GetString() << std::endl;
					m_materials.push_back(material);
				}
				else {
					m_materials.push_back(nullptr);
				}
			}
		}
	}

	void ModelComponent::UpdateGui() {
		ImGui::TextColored({ 0.0, 1.0, 0.0, 1.0 }, "Model");
		if (m_model) {
			ImGui::Text("%s", m_model->GetName().c_str());
		}
		else {
			ImGui::Text("%s", "None");
		}

		ImGui::Separator();
		for (short index = 0; index < m_materials.size(); index++) {
			if (m_materials.at(index)) {
				ImGui::Text("Material [%d] - %s", index, m_materials.at(index)->GetName().c_str());
			}
			else {
				ImGui::Text("Material [%d] - %s", index, "Null");
			}
		}
	}
}