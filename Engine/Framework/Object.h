#pragma once

#include "Serialization/JSON.h"

#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this);}

namespace ChiefEngine {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;
		CLASS_PROTOTYPE(Object)

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline const std::string& GetName() const { return m_name; }
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline bool IsActive() const { return m_active; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="activeState"></param>
		inline void SetActive(bool activeState = true) { m_active = activeState; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		inline virtual void Read(const JSON::value_t& value) {
			JSON_READ_MEMBER(value, "name", m_name);
			JSON_READ_MEMBER(value, "active", m_active);
		}

	protected:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		inline void SetName(const std::string& name) { m_name = name; }

		std::string m_name = "[DEFAULT]";
		bool m_active = true;
	};
}