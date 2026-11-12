#include "pch.h"

#include "Engine.h"
#include "CameraControllerComponent.h"

#include "Framework/Actor.h"

namespace ChiefEngine {
    FACTORY_REGISTER(CameraControllerComponent)

        void CameraControllerComponent::Update(float dt) {
        // get camera rotation
        if (G_Engine().GetInput().GetButtonDown(Input::MouseButton::RIGHT)) {
            glm::vec2 axis = G_Engine().GetInput().GetMouseDelta() * m_sensitivity;

            m_yaw -= axis.x;
            m_pitch -= axis.y;
            m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
        }

        glm::quat rotation = glm::quat_cast(glm::eulerAngleYXZ(glm::radians(m_yaw), glm::radians(m_pitch), 0.0f));
        m_owner->SetRotation(rotation);

        m_direction = { 0.0f, 0.0f, 0.0f };
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_W)) m_direction += m_owner->GetTransform().Forward();
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) m_direction -= m_owner->GetTransform().Right();
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_S)) m_direction -= m_owner->GetTransform().Forward();;
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) m_direction += m_owner->GetTransform().Right();
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) m_direction += m_owner->GetTransform().Up();
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_LCTRL)) m_direction -= m_owner->GetTransform().Up();

        if (glm::length2(m_direction) > 0.0f) {
            m_direction = glm::normalize(m_direction);
        }

        m_owner->SetPosition(m_owner->GetTransform().position + m_direction * dt * m_cameraSpeed);
	}

    void CameraControllerComponent::Read(const JSON::value_t& value) {
        Component::Read(value);
        JSON_READ_MEMBER(value, "cameraSpeed", m_cameraSpeed);
        JSON_READ_MEMBER(value, "sensitivity", m_sensitivity);
    }
}