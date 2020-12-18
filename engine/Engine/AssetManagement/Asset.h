#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Asset
{
public:
	Asset(){}
	virtual ~Asset(){}

	virtual void load(){}
	virtual void destroy(){}

	std::string name;

	//Dont modify
	std::string path;
	std::string parems;
	//--

	virtual nlohmann::json to_json() {
		nlohmann::json j;
		j["path"] = path;
		j["parems"] = parems;
		return j;
	}

	virtual void from_json(nlohmann::json& j) {
		path = j["path"];
		parems = j["parems"];
	}
private:

};