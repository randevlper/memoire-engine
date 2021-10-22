set FILEPATH=%1
set FILENAME=%2
set TARGET=%3
set SHADERC="../build/thirdparty/bgfx.cmake/Debug/shaderc.exe"
if %TARGET%==dx11 ( 
    set VS_FLAGS="--platform windows -p vs_5_0 -O 3"
    set FS_FLAGS="--platform windows -p ps_5_0 -O 3"
    goto compile
)
if %TARGET%==opengl (
    set VS_FLAGS="--platform windows -p 120"
    set FS_FLAGS="--platform windows -p 120"
    goto compile
)

echo %TARGET% is wrong
goto finish

:compile

mkdir "%1/%3" 

%SHADERC% --varyingdef %1/varying.def.sc --type v -f %1/vs_%2.sc -o %1/%3/vs_%2.bin
%SHADERC% --varyingdef %1/varying.def.sc --type f -f %1/fs_%2.sc -o %1/%3/fs_%2.bin

:finish
pause