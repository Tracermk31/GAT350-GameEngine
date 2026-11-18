#pragma once

#include "Editor/Editor.h"

#include "Serialization/JSON.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>

#include "glm/gtx/norm.hpp"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ChiefEngine {
    struct Transform : public IGui {
        glm::vec3 position{ 0.0f };
        glm::quat rotation{ glm::identity<glm::quat>() };
        glm::vec3 scale{ 1.0f };

        glm::mat4 matrix;

        glm::vec3 GetRotation() const {return glm::degrees(glm::eulerAngles(rotation)); }
        void SetRotation(const glm::vec3& eulerAngles) { rotation = glm::quat(glm::radians(eulerAngles)); }
        void SetRotation(const glm::quat quatRotation) { rotation = glm::normalize(quatRotation); }
        
        glm::mat4 GetMatrix() const {
            auto mxt = glm::translate(position);
            auto mxr = glm::toMat4(rotation);
            auto mxs = glm::scale(scale);
            
            return (mxt * mxr * mxs);
        }

        glm::vec3 Forward() const { return rotation * glm::vec3{ 0, 0, -1}; }

        glm::vec3 Up() const { return rotation * glm::vec3{ 0, 1, 0}; }

        glm::vec3 Right() const { return rotation * glm::vec3{ 1, 0, 0}; }

         //<summary>
         //
         //</summary>
         //<param name="value"></param>
        inline void Read(const JSON::value_t& value) {
            JSON_READ_BY_DATA(value, position);

            glm::vec3 eulerRotation { 0.0f };
            JSON_READ_MEMBER(value, "rotation", eulerRotation);
            SetRotation(eulerRotation);
            JSON_READ_BY_DATA(value, scale);
        }

        inline void UpdateGui() override {
            ImGui::DragFloat3("Position", glm::value_ptr(position), 1.0f);

            glm::vec3 euler = GetRotation();

            if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 1.0f)) {
                SetRotation(euler);
            }

            ImGui::DragFloat3("Scale", glm::value_ptr(scale), 1.0f);
        }
    };
}