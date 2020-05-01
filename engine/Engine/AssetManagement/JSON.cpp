#include "JSON.h"

JSON::JSON(nlohmann::json json)
{
	_json = json;
}

JSON::~JSON()
{

}

nlohmann::json JSON::getjson()
{
	return _json;
}
