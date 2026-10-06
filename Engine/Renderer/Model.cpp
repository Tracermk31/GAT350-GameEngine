#include "pch.h"

#include "Model.h"

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	void Model::CalculateRadius() {
		m_radius = 0.0f;
		for (const auto& mesh : m_meshes) {
			m_radius = (mesh.GetRadius() > m_radius) ? mesh.GetRadius() : m_radius;
		}
	}
}