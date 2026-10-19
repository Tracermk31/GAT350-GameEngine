#pragma once

namespace ChiefEngine {
	class Rect {
	public:
		Rect() : position{ {0} }, size{ {0} } {};
		Rect(float x, float y, float width, float height) : position{ x, y }, size{ width, height } {};

		glm::vec2 position;
		glm::vec2 size;
	};
}