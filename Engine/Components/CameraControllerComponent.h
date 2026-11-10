#pragma once

#include "Component.h"

namespace ChiefEngine {
	class CameraControllerComponent : public Component {
	public:
		CLASS_PROTOTYPE(CameraControllerComponent)

		void Update(float dt) override;
		void Read(const JSON::value_t& value);
	private:
		glm::vec3 m_direction{ 0.0f };
		float m_cameraSpeed{ 4.0f };

		float m_yaw = 0;
		float m_pitch = 0;
		float m_sensitivity = 1;
	};
}