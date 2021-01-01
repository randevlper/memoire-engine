#include "luabindings.h"

#include <lua.hpp>
#include <string>

#include "Engine/Core/LuaManager.h"

#include "Engine/Core/World.h"
#include "Engine/Core/WorldManager.h"

#include "Engine/Nodes/SpriteRenderer.h"

#include "Engine/AssetManagement/AssetManager.h"
#include "assetmanagement/Dialogue.h"

#include "Engine/Utilities/Debug.h"

#include "Engine/UI/Text.h"

#include "nodes/DialogueWriter.h"

#define LUA_CFUNCTION(name) lua_pushcfunction(L, name); lua_setglobal(L, #name);

//Expects path to dialogue
int startDialouge(lua_State* L) {
	std::string path = lua_tostring(L, -1);
	AssetManager::load(path, "");
	lb::Dialogue* dialogue = AssetManager::get<lb::Dialogue>(path);
	if (dialogue != nullptr) {
		lb::DialogueWriter::startDialouge(dialogue);
	}
	return 0;
}

int progressDialogue(lua_State* L) {
	lb::DialogueWriter::progress();
	return 0;
}

int dialogueClear(lua_State* L) {
	lb::DialogueWriter::clear();
	return 0;
}

int dialogueAddSpriteRenderer(lua_State* L) {
	World* world = me::WorldManager::getWorld();
	if (world != nullptr) {
		const char* name = lua_tostring(L, -1);
		SpriteRenderer* sprite = world->get<SpriteRenderer>(name);
		lb::DialogueWriter::addSpriteRenderer(sprite);
	}
	return 0;
}

int setupWriter(lua_State* L) {
	World* world = me::WorldManager::getWorld();
	if (world != nullptr) {
		const char* d = lua_tostring(L, -2);
		const char* p = lua_tostring(L, -1);
		me::ui::Text* text = world->get<me::ui::Text>(d);
		me::ui::Text* plate = world->get<me::ui::Text>(p);
		lb::DialogueWriter::setTextBox(text, plate);
		text->setText("Writer setup!");
	}
	return 0;
}

void luaBindings(lua_State* L)
{
	LUA_CFUNCTION(startDialouge)
	LUA_CFUNCTION(progressDialogue)
	LUA_CFUNCTION(setupWriter)
	LUA_CFUNCTION(dialogueClear)
	LUA_CFUNCTION(dialogueAddSpriteRenderer)


	Debug::Log("Setup Librarian LUA!");
}

void lb::InitLuaBindings()
{
	LuaManager::addBindings(luaBindings);
}
