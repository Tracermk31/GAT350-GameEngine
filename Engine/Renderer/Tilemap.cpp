#include "pch.h"

#include "Tilemap.h"
#include "Texture.h"
#include "Renderer.h"

#include "Core/EngineStrings.h"

#include "Serialization/JSON.h"

namespace ChiefEngine {
	bool Tilemap::Load(const std::string& filename, Renderer& renderer) {
		// load json
		JSON::document_t document;
		if (!JSON::Load(filename, document)) {
			std::cerr << "Could not load Tilemap " << filename << std::endl;
			return false;
		}

		// read tilemap data
		JSON_READ_MEMBER_REQUIRED(document, "tilewidth", m_tileWidth);
		JSON_READ_MEMBER_REQUIRED(document, "tileheight", m_tileHeight);

		// read tilemap layers
		if (JSON_HAS_BY_NAME(document, "layers")) {
			for (auto& layerValue : JSON_GET_BY_NAME(document, "layers").GetArray()) {
				Layer layer;

				JSON_READ_MEMBER_REQUIRED(layerValue, "height", layer.height);
				JSON_READ_MEMBER_REQUIRED(layerValue, "width", layer.width);
				JSON_READ_MEMBER_REQUIRED(layerValue, "data", layer.data);

				// load texture from properties
				if (JSON_HAS_BY_NAME(layerValue, "properties")) {
					for (auto& propertyValue : JSON_GET_BY_DATA(layerValue, properties).GetArray()) {
						std::string name;
						JSON_READ_BY_DATA(propertyValue, name);

						// check if property name is TextureName
						if (EqualsIgnoreCase(name, "texture_name")) {
							// read texture name value (texture name)
							std::string value;
							JSON_READ_BY_DATA(propertyValue, value);

							layer.texture = Resources().Get<Texture>(value, renderer);
							if (!layer.texture) {
								std::cerr << "Could not read tilemap layer texture " << value << std::endl;
							}
						}
						else if (EqualsIgnoreCase(name, "hasCollision")) {
							JSON_READ_MEMBER(propertyValue, "value", layer.hasCollision);
						}
					}
				}

				m_layers.push_back(layer);
			}
		}
		return true;
	}

	Rect Tilemap::GetTileRect(const Layer& layer, int tileId) {
		if (tileId <= 0) {
			return Rect();
		}
		Vector2 textureSize = layer.texture->GetSize();
		short tilesPerRow = (short)(textureSize.x / m_tileWidth);
		short column = (tileId - 1) % tilesPerRow;
		short row = (tileId - 1) / tilesPerRow;

		return Rect((float)(column * m_tileWidth), (float)(row * m_tileHeight), (float)m_tileWidth, (float)m_tileHeight);
	}

	Vector2 Tilemap::GetTilePosition(const Layer& layer, int tileIndex) {
		short column = tileIndex  % layer.width;
		short row = tileIndex / layer.width;

		return Vector2((float)(column * m_tileWidth), (float)(row * m_tileHeight));
	}
}