@echo off
set /p SHADERNAME="Enter shader name: "
@echo on
"../build/thirdparty/bgfx.cmake/Debug/shaderc.exe" --varyingdedf src/%SHADERNAME%/varying.def.sc --platform windows -p vs_5_0 -O 3 --type v -o compiled/hlsl/vs_%SHADERNAME%.bin -f src/%SHADERNAME%/vs_%SHADERNAME%.sc --disasm
"../build/thirdparty/bgfx.cmake/Debug/shaderc.exe" --varyingdedf src/%SHADERNAME%/varying.def.sc --platform windows -p ps_5_0 -O 3 --type f -o compiled/hlsl/fs_%SHADERNAME%.bin -f src/%SHADERNAME%/fs_%SHADERNAME%.sc --disasm
pause