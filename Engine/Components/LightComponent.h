#pragma once

#include "RendererComponent.h"

#include "Renderer/Light.h"

namespace ChiefEngine {
	class LightComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(LightComponent)

		void Draw(const class Renderer& renderer) const override;
		void Read(const JSON::value_t& value) override;

		LightData GetLightData() const;
	private:
		LightType m_type;
		glm::vec3 m_color{ 1.0f };
		float m_intensity = 1.0f;
		float m_range = 20.0f;
		float m_innerAngle = 20.0f;
		float m_outerAngle = 30.0f;
	};
}
