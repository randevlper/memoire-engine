@echo off
set /p SHADERNAME="Enter shader name: "
set /p PROJECTNAME="Enter project name: "
@echo on
shaderc -f %SHADERNAME%/vs_%SHADERNAME%.sc --varyingdedf %SHADERNAME%/varying.def.sc --type v -platform windows -o ../%PROJECTNAME%/assets/shaders/vs_%SHADERNAME%.bin
shaderc -f %SHADERNAME%/fs_%SHADERNAME%.sc --varyingdedf %SHADERNAME%/varying.def.sc --type f -platform windows -o ../%PROJECTNAME%/assets/shaders/fs_%SHADERNAME%.bin
pause