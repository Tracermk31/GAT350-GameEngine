#pragma once

#include <box2d/box2d.h>
#include <memory>

namespace ChiefEngine {
	class Physics {
	public:
		Physics() = default;
		
		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static Vector2 ScreenToWorld(const Vector2& screen) {
			return screen / m_pixelsPerUnit;
		}

		static Vector2 WorldToScreen(const Vector2& world) {
			return world * m_pixelsPerUnit;
		}

		static b2Vec2 ToB2(const Vector2& vector2) {
			return b2Vec2(vector2.x, vector2.y);
		}

		static Vector2 ToVector2(const b2Vec2& b2Vector2) {
			return Vector2(b2Vector2.x, b2Vector2.y);
		}

		static float m_pixelsPerUnit;

		friend class PhysicsBody;
	private:
		void ProcessCollisionEvents();

		b2WorldId m_worldId;
	};
}