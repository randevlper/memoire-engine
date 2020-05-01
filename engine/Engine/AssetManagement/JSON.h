#pragma once
#include "Asset.h"
#include <nlohmann/json.hpp>

class JSON : public Asset
{
public:
	JSON(nlohmann::json json);
	~JSON() override;

	nlohmann::json getjson();

private:
	nlohmann::json _json;
};