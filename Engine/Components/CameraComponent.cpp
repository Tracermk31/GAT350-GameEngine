#include "pch.h"

#include "Engine.h"
#include "CameraComponent.h"

#include "Core/Factory.h"

#include "Framework/Actor.h"

namespace ChiefEngine {
	FACTORY_REGISTER(CameraComponent)

	void CameraComponent::Start() {
		m_aspectRatio = G_Engine().GetRenderer().getWindowWidth() / G_Engine().GetRenderer().getWindowHeight();
		m_forward = m_owner->GetTransform().Forward();
	}

	void CameraComponent::Update(float dt) {
		m_view = glm::lookAtRH(m_owner->GetTransform().position, m_owner->GetTransform().position + m_forward, glm::vec3{ 0.0f, 1.0f, 0.0f });
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
	}

	void CameraComponent::Read(const JSON::value_t& value) {
		Component::Read(value);
		JSON_READ_MEMBER(value, "fov", m_fov);
		JSON_READ_MEMBER(value, "farPlane", m_farPlane);
		JSON_READ_MEMBER(value, "nearPlane", m_nearPlane);
	}
}