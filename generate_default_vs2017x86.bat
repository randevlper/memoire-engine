if not exist build mkdir build
Pushd build
cmake ../ -G "Visual Studio 15 2017"
pause