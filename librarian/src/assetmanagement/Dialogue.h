#pragma once
#include "Engine/AssetManagement/Asset.h"
#include <nlohmann/json.hpp>

#define DIALOGUE_FILE_TYPE ".dialogue"

namespace lb {

	struct DialogueLine
	{
		enum CharacterCommand
		{
			SAY,
			SPRITE //For now only changing the sprite
		};

		std::string name = "";
		std::string character = "";
		CharacterCommand characterCommand = CharacterCommand::SAY;
		std::string value = "";

		DialogueLine(std::string const& n, std::string const& v) {
			name = n;
			value = v;
		}

		DialogueLine(nlohmann::json j) {
			from_json(j);
		}

		nlohmann::json to_json() {
			nlohmann::json retval;
			retval["name"] = name;
			retval["character"] = character;
			retval["value"] = value;
			retval["characterCommand"] = characterCommand;
			return retval;
		}
		void from_json(nlohmann::json j) {
			name = j["name"];
			value = j["value"];
			character = j["character"];
			characterCommand = j["characterCommand"];
		}
	};

	//Tell Dialouge writer CharacterLeft is usable
	//Set CharacterLeft as [Character]

	//[Character]      [Enum Commnad] [Value]
	//[Character Name] [Command]      [Text]
	//[Character Name] [Command]      [SpriteChange]


	class Dialogue : public Asset
	{
	public:
		Dialogue();
		Dialogue(nlohmann::json& j);
		~Dialogue() override;
		std::vector<DialogueLine> lines;

		nlohmann::json to_json() {
			nlohmann::json retval = Asset::to_json();
			for (size_t i = 0; i < lines.size(); i++)
			{
				retval["lines"][i] = lines[i].to_json();
			}
			return retval;
		}

		//Need to implment hot reload to hide from_json
		void from_json(nlohmann::json& j) override {
			lines.clear();
			Asset::from_json(j);
			for (auto& [key, value] : j["lines"].items()) {
				DialogueLine newItem(value);
				lines.push_back(value);
			}
		}

	private:
		
	};
}