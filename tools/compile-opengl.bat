SET SHADERNAME=font
shaderc -f %SHADERNAME%/vs_%SHADERNAME%.sc --varyingdedf %SHADERNAME%/varying.def.sc --type v -platform windows -o %SHADERNAME%/vs_%SHADERNAME%.bin
shaderc -f %SHADERNAME%/fs_%SHADERNAME%.sc --varyingdedf %SHADERNAME%/varying.def.sc --type f -platform windows -o %SHADERNAME%/fs_%SHADERNAME%.bin
pause