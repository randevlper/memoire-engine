#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Node
{
public:
	Node();
	virtual ~Node();
	virtual void render();

	void setName(std::string value);
	std::string getName() const;

private:
	std::string _name;
};

inline void to_json(nlohmann::json& j, const Node& n) {
	j["name"] = n.getName();
}

inline void from_json(const nlohmann::json& j, Node& n) {
	n.setName(j.at("name"));
}