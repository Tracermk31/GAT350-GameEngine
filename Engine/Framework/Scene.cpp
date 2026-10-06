#include "pch.h"

#include "Scene.h"

#include "Components/ColliderComponent.h"

#include "Core/Factory.h"

#include "Renderer/Renderer.h"

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="actor"></param>
	void Scene::AddActor(std::unique_ptr <Actor> actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="maxX"></param>
	/// <param name="maxY"></param>
	void Scene::Update(float dt, float maxX, float maxY) {
		for (auto& actor : m_actors) {
			actor->Update(dt, maxX, maxY);
		}

		for (auto& actor : m_actors) {
			if (actor->m_destroyed) {
				actor->OnDestroy();
			}
		}

		std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });

		for (auto& actor : m_pendingActors) {
			actor->Start();
			m_actors.push_back(std::move(actor));
		}
		m_pendingActors.clear();
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void Scene::Draw(const Renderer& renderer) {
		for (const auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	void Scene::DeleteActors(bool force) {
		if (force) {
			m_actors.clear();
		} else {
			std::erase_if(m_actors, [](auto& actor) { return !actor->IsPersistent(); });
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="sceneName"></param>
	/// <returns></returns>
	bool Scene::Load(const std::string& sceneName) {
		JSON::document_t document;
		if (JSON::Load(sceneName, document)) {
			if (JSON_HAS_BY_NAME(document, "actors")) {
				for (auto& actorValue : JSON_GET_BY_NAME(document, "actors").GetArray()) {
					std::string type;	
					JSON_READ_BY_DATA(actorValue, type);

					auto actor = Factory::Instance().Create<Actor>(type);
					actor->Read(actorValue);

					bool prototype = false;
					JSON_READ_BY_DATA(actorValue, prototype);

					if (prototype) {
						std::string name;
						JSON_READ_BY_DATA(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
					} else {
						AddActor(std::move(actor));
					}
				}
			}
			return true;
		} else {
			return false;
		}
	}
}