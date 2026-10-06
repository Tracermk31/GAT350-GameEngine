#pragma once

#include "RendererComponent.h"

#include "Renderer/Texture.h"
#include "Resources/Resource.h"

namespace ChiefEngine {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent)

		void Start() override;

		void Draw(const Renderer& renderer) const override;

		void Read(const JSON::value_t& value) override;

		/// <summary>
		/// Getter for the m_texture member variable that stores the information necessary for a texture
		/// </summary>
		/// <returns>m_texture member value</returns>
		inline const resource_t<Texture> GetTexture() const {
			return m_texture;
		}

		inline const Rect& GetSourceRectangle() const {
			return m_sourceRectangle;
		}

		inline const Vector2& GetSize() const{
			return m_size;
		}

		inline void FlipHorizontal(bool flipHorizontal = true) {
			m_flipHorizontal = flipHorizontal;
		}

		inline bool IsFlipHorizontal() const {
			return m_flipHorizontal;
		}

	protected:
		std::string m_textureName;
		Rect m_sourceRectangle;
		Vector2 m_size{ 0.0f };
		Vector2 m_origin{ 0.5f };
		bool m_flipHorizontal = false;

		resource_t<Texture> m_texture;
	};
}