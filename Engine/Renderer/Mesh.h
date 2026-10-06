#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <vector>

namespace ChiefEngine {
	class Mesh {
	public:
		Mesh() = default;
		Mesh(const std::vector<Vector2>& points, const Color& color) : 
			m_points { points } 
			,m_color{ color } 
		{ }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="points"></param>
		void SetPoints(const std::vector<Vector2>& points) { m_points = points; }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::vector<Vector2>& GetPoints() const { return m_points; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Color& color) { m_color = color; }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const Color& GetColor() const { return m_color; }

		float GetRadius() const;
	private:
		std::vector<Vector2> m_points = { 0.0f };
		Color m_color = { 255.0f };
	};
}