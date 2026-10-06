#pragma once

#include "CharacterBase.h"

namespace ChiefEngine {
    class PlayerController : public CharacterBase {
    public:
        CLASS_PROTOTYPE(PlayerController)

        void Start() override;
        void Update(float dt, float maxX, float maxY) override;

        void OnCollision(Actor* other) override;

        void Read(const JSON::value_t& value) override;
    protected:
        class PhysicsComponent* m_physicsComponent = nullptr;
        class SpriteAnimatorRendererComponent* m_spriteAnimatorRendererComponent = nullptr;

        float m_jumpTimer = 0.0f;
    };
}

