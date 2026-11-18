#pragma once

#include "Editor/Editor.h"

#include "Serialization/JSON.h"

#include <string>

#define CLASS_PROTOTYPE(classname) \
	virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this);} \
	virtual std::string GetClassName() const {return #classname;} \

namespace ChiefEngine {
	class Object : public IGui {
	public:
		Object() = default;
		virtual ~Object() = default;
		CLASS_PROTOTYPE(Object)

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const std::string& GetName() const { return m_name; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		void SetName(const std::string& name) { m_name = name; }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool IsActive() const { return m_active; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="activeState"></param>
		void SetActive(bool activeState = true) { m_active = activeState; }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="value"></param>
		virtual void Read(const JSON::value_t& value) {
			JSON_READ_MEMBER(value, "name", m_name);
			JSON_READ_MEMBER(value, "active", m_active);
		}

		/// <summary>
		/// 
		/// </summary>
		void UpdateGui() override {
			ImGui::Text("Name: %s", m_name.c_str());
		}

	protected:
		std::string m_name = "[DEFAULT]";
		bool m_active = true;
	};
}