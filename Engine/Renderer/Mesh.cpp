#include "pch.h"

#include "Mesh.h"

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	float Mesh::GetRadius() const {
		float radius = 0.0f;
		for (const auto& point : m_points) {
			radius = (point.Length() > radius) ? point.Length() : radius;
		}
		return radius;
	}
}