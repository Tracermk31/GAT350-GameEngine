#pragma once

#include "Shader.h"
#include "Pipeline.h"

#include "Resources/Resource.h"

#include <glm/glm.hpp>

namespace ChiefEngine {
	class Texture;

	struct MaterialData {
		glm::vec4 baseColor{ 1.0f };
		glm::vec2 tiling{ 1.0f };
		glm::vec2 offset{ 0.0f };
		float shininess = 32.0f;
		glm::vec3 padding{ 0.0f };
	};

	class Material : public Resource {
	public:
		bool Load(const std::string& filename, const class Renderer& renderer);

		const MaterialData& GetDefaults() const { return m_defaults; }

		size_t GetTextureSlotCount() const { return m_textureSlots.size(); }
		int GetTextureSlot(const std::string& name) const;

		const Pipeline& GetPipeline() const { return m_pipeline; }
		const resource_t<Texture>& GetDefaultTexture() const { return m_defaultTexture; }

	private:
		resource_t<Shader> m_vertexShader;
		resource_t<Shader> m_fragmentShader;
		Pipeline m_pipeline;

		MaterialData m_defaults;
		std::vector<std::string> m_textureSlots;
		resource_t<Texture> m_defaultTexture;
	};
}