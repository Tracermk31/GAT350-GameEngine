#pragma once

#include "Object.h"

#include "Math/Transform.h"

#include "Renderer/Model.h"

#include "Resources/Resource.h"

#include "Components/Component.h"

#include <memory>
#include <string>

namespace ChiefEngine {
    class Scene;
    class Texture;

    /// <summary>
    /// Parent class for all actors inside of a Scene.
    /// </summary>
    class Actor : public Object {
    public:
        /// <summary>
        /// Default constructor for the Actor class.
        /// </summary>
        Actor() = default;

        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

        virtual void Update(float dt, float maxY, float maxX);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void Start();
        virtual void OnDestroy();

        virtual void OnCollision(Actor* other) {}

        virtual void Read(const JSON::value_t& value) override;

        const Transform& GetTransform() const { return this->m_transform; }
        void SetTransform(const Transform& transform) { m_transform = transform; }

        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        void BeDestroyed() { m_destroyed = true; }
        bool IsDestroyed() const { return m_destroyed; }

        bool SetPersistent(bool persistent) { m_persistent = persistent; }
        bool IsPersistent() const { return m_persistent; }

        std::string GetTag() { return m_tag; }
        Scene* GetScene() { return m_scene; }

        void SetTag(const std::string& tag) {
            m_tag = tag;
        }

        void SetLifespan(float lifespan) {
            m_lifespan = lifespan;
        }

        void AddComponent(std::unique_ptr<Component> component);

        template<std::derived_from<Component> T>
        T* GetComponent();

        friend Scene;
    protected:
        std::string m_tag = "[UNDECIDED]";

        std::vector<std::unique_ptr<Component>> m_components;

        Transform m_transform;
        float m_lifespan{ -1.0f };
        bool m_destroyed{ false };
        bool m_persistent{ false };

        Scene* m_scene{ nullptr };
    };

    template<std::derived_from<Component> T>
    inline T* Actor::GetComponent() {
        for (auto& component : m_components) {
            auto componentType = dynamic_cast<T*>(component.get());
            if (componentType) {
                return componentType;
            }
        }
        return nullptr;
    }
}