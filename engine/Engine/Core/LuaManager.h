#pragma once

typedef struct lua_State lua_State;

#include <vector>
#include <functional>

class LuaManager
{
public:
	static void init();
	static void destroy();

	static void loadLua(const char* lua);
	static void luaFunction(const char* functionName);

	static void addBindings(std::function<void(lua_State*)> func);

private:
	static lua_State* _L;
	static std::vector<std::function<void(lua_State*)>> bindings;

	LuaManager(){}
	~LuaManager(){}
};