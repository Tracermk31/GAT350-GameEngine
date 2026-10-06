#pragma once

#include "CharacterBase.h"

namespace ChiefEngine {
    class EnemyController : public CharacterBase {
    public:
        CLASS_PROTOTYPE(EnemyController)

        void Start() override;
        void Update(float dt, float maxX, float maxY) override;

        void OnCollision(Actor* other) override;

        void Read(const JSON::value_t& value) override;
    protected:
        class PhysicsComponent* m_physicsComponent = nullptr;
        class SpriteAnimatorRendererComponent* m_spriteAnimatorRendererComponent = nullptr;

        short m_pointValue = 0;
    };
}
