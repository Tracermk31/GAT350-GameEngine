#pragma once

#include "RendererComponent.h"
#include "Resources/ResourceManager.h"

namespace ChiefEngine {
	class TilemapRendererComponent : public RendererComponent {
	public:
		TilemapRendererComponent() = default;
		TilemapRendererComponent(const TilemapRendererComponent& other);

		CLASS_PROTOTYPE(TilemapRendererComponent)

		void Start() override;
		void Draw(const class Renderer& renderer) const override;

		void Read(const JSON::value_t& value) override;
	private:
		std::string m_tilemapName;
		resource_t<class Tilemap> m_tilemap;
		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}