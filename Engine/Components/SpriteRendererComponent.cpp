#include "pch.h"

#include "Engine.h"
#include "SpriteRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(SpriteRendererComponent)

	/// <summary>
	/// 
	/// </summary>
	void SpriteRendererComponent::Start() {
		if (!m_textureName.empty()) {
			m_texture = Resources().Get<Texture>(m_textureName, G_Engine().GetRenderer());
			if (m_texture) {
				m_size = m_texture->GetSize();
			}
		}
	}

	/// <summary>
	/// Function to draw the texture onto a screen using a provided renderer. Retrieves all necessary texture
	/// information from the m_texture member variable and position and size information from the m_owner member variable.
	/// </summary>
	/// <param name="renderer">The Renderer used to draw the texture</param>
	void SpriteRendererComponent::Draw(const Renderer& renderer) const {
		if (m_texture) {
			if (m_sourceRectangle.size.x > 0 && m_sourceRectangle.size.y > 0) {
				renderer.DrawTexture(*m_texture,
					m_sourceRectangle,
					GetOwner()->GetTransform().position.x,
					GetOwner()->GetTransform().position.y,
					GetOwner()->GetTransform().rotation,
					GetOwner()->GetTransform().scale,
					m_flipHorizontal,
					false,
					m_origin);
			} else {
				renderer.DrawTexture(*m_texture,
					GetOwner()->GetTransform().position.x,
					GetOwner()->GetTransform().position.y,
					GetOwner()->GetTransform().rotation,
					GetOwner()->GetTransform().scale,
					m_flipHorizontal,
					false,
					m_origin);
			}
		}
	}

	/// <summary>
	/// Reads texture informatoin from a provided JSON file
	/// </summary>
	/// <param name="value">JSON value to be read from</param>
	void SpriteRendererComponent::Read(const JSON::value_t& value) {
		RendererComponent::Read(value);

		JSON_READ_MEMBER(value, "texture", m_textureName);
		JSON_READ_MEMBER(value, "flipHorizontal", m_flipHorizontal);
		JSON_READ_MEMBER(value, "origin", m_origin);
	}
}