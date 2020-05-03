#pragma once
#include "nlohmann/json.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace nlohmann {
	template<>
	struct adl_serializer<glm::vec4>
	{
		static void to_json(json& j, const glm::vec4& val) {
			j.push_back(val.x);
			j.push_back(val.y);
			j.push_back(val.z);
			j.push_back(val.w);
		}

		static void from_json(const json& j, glm::vec4& val) {
			val.x = j[0];
			val.y = j[1];
			val.z = j[2];
			val.w = j[3];
		}
	};

	template<>
	struct adl_serializer<glm::vec2>
	{
		static void to_json(json& j, const glm::vec2& val) {
			j.push_back(val.x);
			j.push_back(val.y);
		}

		static void from_json(const json& j, glm::vec2& val) {
			val.x = j[0];
			val.y = j[1];
		}
	};

	template<>
	struct adl_serializer<glm::ivec2>
	{
		static void to_json(json& j, const glm::ivec2& val) {
			j.push_back(val.x);
			j.push_back(val.y);
		}

		static void from_json(const json& j, glm::ivec2& val) {
			val.x = j[0];
			val.y = j[1];
		}
	};
}