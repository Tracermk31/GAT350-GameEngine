#pragma once

#include "Resources/ResourceManager.h"
#include "Math/Rect.h"

#include <vector>

namespace ChiefEngine {
	class Tilemap :public Resource {
	public:
		struct Layer {
			int width = 0;
			int height = 0;
			bool hasCollision = false;
			std::vector<int> data;
			resource_t<class Texture> texture;
		};

		bool Load(const std::string& filename, class Renderer& renderer);

		const std::vector<Layer>& GetLayers() const { return m_layers; }
		Rect GetTileRect(const Layer& layer, int tileId);
		Vector2 GetTilePosition(const Layer& layer, int tileIndex);
	private:
		short m_tileWidth;
		short m_tileHeight;

		std::vector<Layer>m_layers;
	};
}