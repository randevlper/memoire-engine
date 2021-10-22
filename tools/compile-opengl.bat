@echo off
set /p SHADERNAME="Enter shader name: "
@echo on
"../build/thirdparty/bgfx.cmake/Debug/shaderc.exe" -f src/%SHADERNAME%/vs_%SHADERNAME%.sc --varyingdedf src/%SHADERNAME%/varying.def.sc --type v -platform windows -o compiled/glsl/vs_%SHADERNAME%.bin
"../build/thirdparty/bgfx.cmake/Debug/shaderc.exe" -f src/%SHADERNAME%/fs_%SHADERNAME%.sc --varyingdedf src/%SHADERNAME%/varying.def.sc --type f -platform windows -o compiled/glsl/fs_%SHADERNAME%.bin
pause