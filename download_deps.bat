if not exist thirdparty mkdir thirdparty
SET DLLOC="./thirdparty/box2D-cmake.zip"
SET DLURL="https://github.com/tobanteGaming/Box2D-cmake/archive/master.zip"
call download_file.bat
SET DLLOC="./thirdparty/box2D.zip"
SET DLURL="https://github.com/erincatto/Box2D/archive/master.zip"
call download_file.bat
SET DLLOC="./thirdparty/entt.zip"
SET DLURL="https://github.com/skypjack/entt/archive/v3.0.0.zip"
call download_file.bat
SET DLLOC="./thirdparty/SDL2.zip"
SET DLURL="https://www.libsdl.org/release/SDL2-2.0.9.zip"
call download_file.bat
SET DLLOC="./thirdparty/glm.zip"
SET DLURL="https://github.com/g-truc/glm/archive/stable.zip"
call download_file.bat
SET DLLOC="./thirdparty/zlib.zip"
SET DLURL="https://github.com/madler/zlib/archive/master.zip"
call download_file.bat


pushd thirdparty
if not exist stb mkdir stb
pushd ..
SET DLLOC="./thirdparty/stb/stb_image.h"
SET DLURL="https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
call download_file.bat

DEL /F/Q/S .wget-hsts > NUL