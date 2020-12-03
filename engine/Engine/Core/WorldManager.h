#pragma once
#include <string>

class World;
class Camera;


namespace me {
	class WorldManager
	{
	public:

		//Creates an empty world
		static void loadWorld();

		//Loads a world from a JSON world file
		static bool loadWorld(std::string path);

		static bool postLogic();

		static void unLoadWorld();

		static void tick();
		static void render();

		static World* getWorld();

	private:
		static World* _currentWorld;
		static World* _toLoadWorld;
		static Camera* _toLoadCamera;
		static std::string _toLoadWorldPath;
	};
}