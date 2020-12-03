#include "luabindings.h"

#include <lua.hpp>

#include "Engine/Core/LuaManager.h"

#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"

#include "Engine/Utilities/Debug.h"

#include "Engine/UI/Text.h"

#include "nodes/DialogueWriter.h"

int setupWriter(lua_State* L) {
	World* world = me::WorldManager::getWorld();
	if (world != nullptr) {
		const char* name = lua_tostring(L, -1);
		me::ui::Text* text = world->get<me::ui::Text>(name);
		lb::DialogueWriter::setTextBox(text);
		text->setText("Writer setup!");
	}
	return 0;
}

void luaBindings(lua_State* L)
{
	lua_pushcfunction(L, setupWriter); 
	lua_setglobal(L, "setupWriter");
	Debug::Log("Setup Librarian LUA!");
}

void lb::InitLuaBindings()
{
	LuaManager::addBindings(luaBindings);
}
