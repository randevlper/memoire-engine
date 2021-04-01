if not exist build mkdir build
Pushd build
cmake ../ %PAREM%
Pushd ..
pause