#pragma once
#include "Engine/AssetManagement/Asset.h"
#include <nlohmann/json.hpp>

namespace lb {

	struct DialogueLine
	{
		std::string name;
		std::string text;

		DialogueLine(std::string n, std::string t) {
			name = n; text = t;
		}

		DialogueLine(nlohmann::json j) {
			from_json(j);
		}

		nlohmann::json to_json() {
			nlohmann::json retval;
			retval["name"] = name;
			retval["text"] = text;
			return retval;
		}
		void from_json(nlohmann::json j) {
			name = j["name"];
			text = j["text"];
		}
	};

	class Dialogue : public Asset
	{
	public:
		Dialogue();
		Dialogue(nlohmann::json& j);
		~Dialogue() override;
		std::vector<DialogueLine> lines;

		nlohmann::json to_json() {
			nlohmann::json retval;
			for (size_t i = 0; i < lines.size(); i++)
			{
				retval["lines"][i] = lines[i].to_json();
			}
			return retval;
		}

		//Need to implment hot reload to hide from_json
		void from_json(nlohmann::json& j) {
			lines.clear();
			for (auto& [key, value] : j["lines"].items()) {
				DialogueLine newItem(value);
				lines.push_back(value);
			}
		}

	private:
		
	};
}