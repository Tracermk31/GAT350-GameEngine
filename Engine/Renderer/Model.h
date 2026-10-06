#pragma once

#include "Mesh.h"

namespace ChiefEngine {
	class Model {
	public:
		Model() = default;
		Model(const std::vector<Mesh>& meshes) : m_meshes{ meshes } {
			CalculateRadius();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="mesh"></param>
		inline void AddMesh(const Mesh& mesh) { 
			m_meshes.push_back(mesh); 
			CalculateRadius();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="meshes"></param>
		inline void SetMeshes(const std::vector<Mesh>& meshes) { 
			m_meshes = meshes;
			CalculateRadius();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::vector<Mesh>& GetMeshes() const { return m_meshes; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline float GetRadius() const { return m_radius; }
		void CalculateRadius();
	private:
		float m_radius = 0.0f;
		std::vector<Mesh> m_meshes;
	};
}