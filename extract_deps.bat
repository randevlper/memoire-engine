7za.exe x thirdparty\entt.zip -o%CD%\thirdparty\entt\
xcopy /s /y /f thirdparty\entt\entt-3.0.0 thirdparty\entt
RMDIR thirdparty\entt\entt-3.0.0 /Q/S
::DEL /F/Q/S thirdparty\entt.zip > NUL

7za.exe x thirdparty\box2D-cmake.zip -o%CD%\thirdparty\Box2D\
xcopy /s /y /f thirdparty\Box2D\Box2D-cmake-master thirdparty\Box2D\
RMDIR thirdparty\Box2D\Box2D-cmake-master /Q/S
::DEL /F/Q/S thirdparty\box2D-cmake.zip > NUL

7za.exe x thirdparty\box2D.zip -o%CD%\thirdparty\Box2D\
xcopy /s /y /f thirdparty\Box2D\Box2D-master thirdparty\Box2D\Box2D\
RMDIR thirdparty\Box2D\Box2D-master /Q/S
::DEL /F/Q/S thirdparty\box2D.zip > NUL

7za.exe x thirdparty\SDL2.zip -o%CD%\thirdparty\SDL2\
xcopy /s /y /f thirdparty\SDL2\SDL2-2.0.9 thirdparty\SDL2
RMDIR thirdparty\SDL2\SDL2-2.0.9 /Q/S
::DEL /F/Q/S thirdparty\SDL2.zip > NUL