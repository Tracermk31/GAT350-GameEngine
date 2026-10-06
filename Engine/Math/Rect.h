#pragma once

#include "Vector2.h"

namespace ChiefEngine {
	class Rect {
	public:
		Rect() : position{ {0} }, size{ {0} } {};
		Rect(float x, float y, float width, float height) : position{ x, y }, size{ width, height } {};

		Vector2 position;
		Vector2 size;
	};
}