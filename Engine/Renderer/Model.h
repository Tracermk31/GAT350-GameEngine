#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "MaterialInstance.h"

#include "Resources/Resource.h"

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

// forward declare assimp types so the header doesn't pull in assimp
struct aiNode;
struct aiMesh;
struct aiScene;

namespace ChiefEngine {
	class Model : public Resource {
	public:
		struct Vertex {
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

		// each mesh owns its own vertex and index buffer
		struct Mesh {
			std::unique_ptr<VertexBuffer> vertexBuffer;
			std::unique_ptr<IndexBuffer> indexBuffer;
			uint32_t materialIndex = 0;
		};

		bool Load(const std::string& filename, const class Renderer& renderer);

		// binds and draws every mesh, call between BeginFrame and EndFrame with a pipeline set
		void Draw(const class Renderer& renderer, const std::vector<resource_t<class MaterialInstance>>& overrides) const;

		friend IndexBuffer;
		friend VertexBuffer;

	private:
		void ProcessNode(aiNode* node, const aiScene* scene, const class Renderer& renderer);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene, const class Renderer& renderer);

		void LoadMaterials(const aiScene* scene, const std::string& directory, const class Renderer& renderer);

		std::vector<Mesh> m_meshes;
		std::vector<MaterialInstance> m_materials;
	};
}
