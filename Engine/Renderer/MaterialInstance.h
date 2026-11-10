#pragma once

#include "Material.h"
#include "Framework/Object.h"

#include "Resources/Resource.h"

namespace ChiefEngine {
	class Texture;

	class MaterialInstance : public Resource {
	public:
		MaterialInstance() = default;
		explicit MaterialInstance(const resource_t<Material> material);

		void Initialize(const resource_t<Material>& material);
		bool Load(const std::string& filename, const class Renderer& renderer);

		void Bind(SDL_GPUCommandBuffer* commandBuffer, SDL_GPURenderPass* renderPass) const;

		void SetTexture(size_t slot, resource_t<Texture> texture);
		bool SetTexture(const std::string& name, resource_t<Texture> texture);

		MaterialData& GetData() { return m_data; }
		const MaterialData& GetData() const { return m_data; }

		const Material& GetMaterial() const { return *m_material; }

	private:
		resource_t<Material> m_material;
		MaterialData m_data;
		std::vector<resource_t<class Texture>> m_textures;
	};
}