#pragma once

#include "Resource.h"

#include "Core/Singleton.h"

#include <map>
#include <string>
#include <iostream>

namespace ChiefEngine {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template<typename T, typename ... Args>
			requires std::derived_from<T, Resource>
		resource_t<T> Get(const std::string& name, Args&& ... args);

		template<typename T, typename ... Args>
			requires std::derived_from<T, Resource>
		resource_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);
	private:
		std::map<std::string, resource_t<Resource>> m_resources;
	};

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="id"></param>
	/// <param name="name"></param>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename T, typename ...Args>
		requires std::derived_from<T, Resource>
	inline resource_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args&& ... args) {
		auto iterator = m_resources.find(id);
		// check if exists
		if (iterator != m_resources.end()) {
			// get value in iterator
			auto base = iterator->second;
			// cast to data type T
			auto resource = std::dynamic_pointer_cast<T>(base);
			// check if cast was successful
			if (resource == nullptr) {
				std::cerr << "Resource type mismatch: " << id << std::endl;
				return resource_t<T>();
			}

			// return resource
			return resource;
		}

		// load resource
		resource_t<T> resource = std::make_shared<T>();
		if (!resource->Load(name, std::forward<Args>(args)...)) {
			std::cerr << "Could not load resource: " << name << std::endl;
			return resource_t<T>();
		}

		// add resource to resource manager
		m_resources[id] = resource;

		return resource;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="name"></param>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename T, typename ... Args>
		requires std::derived_from<T, Resource>
	inline resource_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) {
		return GetWithID<T>(name, name, std::forward<Args>(args)...);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}