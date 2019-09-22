mkdir thirdparty
git submodule init
git submodule update
cd thirdparty/bgfx.cmake
git submodule init
git submodule update
cd ../stb-cmake
git submodule init
git submodule update
cd ../glm
git checkout 0.9.9.5