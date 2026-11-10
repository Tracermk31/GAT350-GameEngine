#include "pch.h"

#include "LightComponent.h"

#include "Core/Factory.h"

#include "Framework/Actor.h"

namespace ChiefEngine {
	FACTORY_REGISTER(LightComponent)

	void LightComponent::Draw(const class Renderer& renderer) const {}

	void LightComponent::Read(const JSON::value_t& value) {
		std::string typeName;
		JSON_READ_MEMBER(value, "light_type", typeName);
		if (typeName == "directional") m_type = LightType::DIRECTIONAL;
		else if (typeName == "spot") m_type = LightType::SPOT;
		else m_type = LightType::POINT;

		JSON_READ_MEMBER(value, "color", m_color);
		JSON_READ_MEMBER(value, "intensity", m_intensity);
		JSON_READ_MEMBER(value, "range", m_range);
		JSON_READ_MEMBER(value, "innerAngle", m_innerAngle);
		JSON_READ_MEMBER(value, "outerAngle", m_outerAngle);
	}

	LightData LightComponent::GetLightData() const {
		const Transform& transform = m_owner->GetTransform();

		LightData lightData = {
			.position = transform.position,
			.type = m_type,
			.direction = transform.Forward(),
			.range = m_range,
			.color = m_color,
			.intensity = m_intensity,
			.innerCutoff = glm::cos(glm::radians(m_innerAngle)),
			.outerCutoff = glm::cos(glm::radians(m_outerAngle))
		};

		return lightData;
	}
}