#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class CameraComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(CameraComponent)

		void Draw(const class Renderer& renderer) const override {};
		void Update(float dt) override;
		void Read(const JSON::value_t& value) override;
	private:
		glm::mat4x4 m_view{ 0.0f };
		glm::mat4x4 m_projection{ 0.0f };

		float m_fov{ 70.0f };
		float m_nearPlane{ 0.001f };
		float m_farPlane{ 300.0f };
	};
}
