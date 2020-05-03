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

	//Dont modify
	std::string name;
	//Dont modify
	std::string parems;

	nlohmann::json to_json() {
		nlohmann::json j;
		j["name"] = name;
		j["parems"] = parems;
		return j;
	}
private:

};