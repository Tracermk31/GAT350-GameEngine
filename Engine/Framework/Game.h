#pragma once

#include "Scene.h"

#include <memory>

namespace ChiefEngine {
	class Game {
	public:
		Game();
		virtual ~Game();

		virtual bool Initialize();
		virtual void Shutdown() const {}

		virtual void Update(float dt, float maxX, float maxY);
		virtual void Draw(class Renderer& renderer, float maxX, float maxY) ;

		void SetScene(std::unique_ptr<Scene> scene);
	protected:
		std::unique_ptr<Scene> m_scene;
	};
}