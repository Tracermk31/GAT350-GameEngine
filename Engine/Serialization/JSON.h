#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <string>
#include <vector>

#include <rapidjson/document.h>

#define JSON_HAS_BY_NAME(value, name) value.HasMember(name)
#define JSON_HAS_BY_DATA(value, data) value.HasMember(#data)

#define JSON_READ_BY_DATA(value, data) ChiefEngine::JSON::Read(value, #data, data)
#define JSON_READ_MEMBER(value, name, data) ChiefEngine::JSON::Read(value, name, data)

#define JSON_READ_BY_DATA_REQUIRED(value, data) ChiefEngine::JSON::Read(value, #data, data, true)
#define JSON_READ_MEMBER_REQUIRED(value, name, data) ChiefEngine::JSON::Read(value, name, data, true)

#define JSON_GET_BY_DATA(value, data) value[#data]
#define JSON_GET_BY_NAME(value, name) value[name]

namespace ChiefEngine::JSON {
	using value_t = rapidjson::Value;
	using document_t = rapidjson::Document;

	bool Load(const std::string& filename, document_t& document);

	// read json data
	bool Read(const value_t& value, const std::string& name, short& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, unsigned short& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, int& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, unsigned int& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, bool& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, float& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, std::string& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, Vector2& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, Vector3& data, bool required = false);
	bool Read(const value_t& value, const std::string& name, std::vector<int>& data, bool required = false);
}