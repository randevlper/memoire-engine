7za.exe x thirdparty\entt.zip -o%CD%\thirdparty\entt\
xcopy /s /y /f thirdparty\entt\entt-3.0.0 thirdparty\entt
RMDIR thirdparty\entt\entt-3.0.0 /Q/S
#DEL /F/Q/S thirdparty\entt.zip > NUL

7za.exe x thirdparty\SDL2.zip -o%CD%\thirdparty\SDL2\
xcopy /s /y /f thirdparty\SDL2\SDL2-2.0.9 thirdparty\SDL2
RMDIR thirdparty\SDL2\SDL2-2.0.9 /Q/S
#DEL /F/Q/S thirdparty\SDL2.zip > NUL

7za.exe x thirdparty\glm.zip -o%CD%\thirdparty\glm\
xcopy /s /y /f thirdparty\glm\glm-stable thirdparty\glm
RMDIR thirdparty\glm\glm-stable /Q/S
#DEL /F/Q/S thirdparty\glm.zip > NUL

7za.exe x thirdparty\zlib.zip -o%CD%\thirdparty\zlib\
xcopy /s /y /f thirdparty\zlib\zlib-master thirdparty\zlib
RMDIR thirdparty\zlib\zlib-master /Q/S
#DEL /F/Q/S thirdparty\zlib.zip > NUL