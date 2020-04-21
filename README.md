# Memoire-Engine
Memoire is a game engine framework built for 2D windows games.

# Installation and Building
- git clone --recursive https://github.com/randevlper/memoire-engine
- Requires CMAKE on PATH
- Quick setup cmake_generate.bat


# Features
- Transforms
- Single Pass Tilemap
- PNG Textures

# In-Progress
- Virtual Novel game
- UI System
- Audio System
- Basic Scene System

# Minimal Setup


May not be up to date as code is in heavy development
```c++
#include "Engine/Core/Context.h"
#include "Engine/Core/Renderer.h"
#include "Engine/Nodes/Camera.h"

int main(int argc, char** argv) {
	ContextWindowParems cWinParems = { "Hello World", 1280, 720, 60 , argc, argv};
	Context::init(&cWinParems);
	if (Context::getErrorCode() != 0) {
		return Context::getErrorCode();
	}

	Camera* cam = world->create <Camera>();
	cam->transform.setLocalPosition({ 0,0 });
	Renderer::setCamera(cam);

	while (!Context::getShouldClose())
	{
		Context::tick();

		Renderer::render();
	}

	Context::quit();

	return 0;
}
```


