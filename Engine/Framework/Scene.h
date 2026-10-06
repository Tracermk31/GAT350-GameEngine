#pragma once

#include "Actor.h"

#include "Components/ColliderComponent.h"

#include <memory>
#include <string>
#include <vector>

namespace ChiefEngine {
	class Game;

	class Scene {
	private:
		std::vector<std::unique_ptr<Actor>> m_actors;
		std::vector<std::unique_ptr<Actor>> m_pendingActors;

		Game* m_game = nullptr;
	public:
		void AddActor(std::unique_ptr <Actor> actor);
		void DeleteActors(bool force = false);

		bool Load(const std::string& sceneName);

		void Update(float dt, float maxX, float maxY);
		void Draw(const class Renderer& renderer);

		void SetGame(Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="name"></param>
		/// <returns></returns>
		template<typename T = Actor>
		inline T* GetActorByName(const std::string& name) {
			for (auto& actor : m_actors) {
				T* tempActor = dynamic_cast<T*>(actor.get());
				if (tempActor && tempActor->m_name._Equal(name)) {
					return tempActor;
				}
			}
			return nullptr;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="tag"></param>
		/// <returns></returns>
		template<typename T = Actor>
		inline T* GetActorByTag(const std::string& tag) {
			for (auto& actor : m_actors) {
				T* tempActor = dynamic_cast<T*>(actor.get());
				if (tempActor && tempActor->m_tag._Equal(tag)) {
					return tempActor;
				}
			}
			return nullptr;
		}
	};
}