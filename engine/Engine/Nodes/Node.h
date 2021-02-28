#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "Engine/Utilities/glmJson.h"

class Node
{
public:
	Node();
	virtual ~Node();
	virtual void render();

	void setName(std::string value);
	std::string getName() const;

	//Probably a lot better way of doing this so we dont have these functions in here
	virtual nlohmann::json to_json() {
		nlohmann::json j;
		j["type"] = _type;
		j["name"] = getName();
		return j;
	}

	virtual void from_json(const nlohmann::json& j) {
		setName(j.at("name"));
	}
	
	std::string getType() {
		return _type;
	}

	unsigned int getSort() {
		return sort;
	}

	void setSort(unsigned int value) {
		sort = value;
	}

private:

protected:
	std::string _name;
	std::string _type;
	unsigned int sort;
};