#include "LuaManager.h"
#include <string>
#include <lua.hpp>

#include "Engine/Utilities/Debug.h"
#include "Engine/Core/WorldManager.h"

#define LUA_CFUNCTION(name) lua_pushcfunction(_L, name); lua_setglobal(_L, #name);

int LoadWorld(lua_State* L)
{
	Debug::Log("Loading world!");
	const char* path = lua_tostring(L, -1);
	Debug::Log(path);
	me::WorldManager::loadWorld(path);
	return 0;
}


LuaManager::LuaManager()
{
	_L = luaL_newstate();
	LUA_CFUNCTION(LoadWorld)

	Debug::Log("Lua State created.");
}

LuaManager::~LuaManager()
{
	lua_close(_L);
}

void LuaManager::test()
{
	luaL_dostring(_L, "x = 69");
	lua_getglobal(_L, "x");
	lua_Number Lx = lua_tonumber(_L, 1);
	Debug::Log("Lua says: " + std::to_string(Lx));
	luaL_dostring(_L, "LoadWorld(\"assets/worlds/test.world\")");
}