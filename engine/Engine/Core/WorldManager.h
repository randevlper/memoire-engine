#pragma once
#include <string>

class World;


namespace me {
	class WorldManager
	{
	public:

		//Creates an empty world
		static void loadWorld();

		//Loads a world from a JSON world file
		static void loadWorld(std::string path);

		static void unLoadWorld();

		static void tick();
		static void render();

		static World* getWorld();

	private:
		static World* _currentWorld;
	};
}