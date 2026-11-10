#pragma once

#include "RendererComponent.h"

namespace ChiefEngine {
	class CameraComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(CameraComponent)

		void Start() override;
		void Draw(const class Renderer& renderer) const override {};
		void Update(float dt) override;
		void Read(const JSON::value_t& value) override;

		const glm::mat4x4& GetView() const { return m_view; }
		const glm::mat4x4& GetProjection() const { return m_projection; }
	private:
		glm::mat4x4 m_view{ 0.0f };
		glm::mat4x4 m_projection{ 0.0f };

		glm::vec3 m_forward{ 0.0 };

		float m_aspectRatio{ 16.0f / 10.0f };
		float m_fov{ 70.0f };
		float m_nearPlane{ 0.001f };
		float m_farPlane{ 300.0f };
	};
}
