#pragma once

#include "Serialization/JSON.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

namespace ChiefEngine {
    struct Transform {
        glm::vec3 position { 0.0f };
        glm::vec3 rotation{ 0.0f };
        glm::vec3 scale{ 1.0f };

        glm::mat4 matrix;

        const glm::mat4& GetMatrix() {
            auto mxt = glm::translate(position);
            auto mxr = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
            auto mxs = glm::scale(scale);
            
            matrix = mxt * mxr * mxs;

            return matrix;
        }
         //<summary>
         //
         //</summary>
         //<param name="value"></param>
        inline void Read(const JSON::value_t& value) {
            JSON_READ_BY_DATA(value, position);
            JSON_READ_BY_DATA(value, rotation);
            JSON_READ_BY_DATA(value, scale);
        }
    };
}