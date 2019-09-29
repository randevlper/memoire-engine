shaderc -f line/vs_line.sc --varyingdedf line/varying.def.sc --type v -platform windows -o line/vs_line.bin
shaderc -f line/fs_line.sc --varyingdedf line/varying.def.sc --type f -platform windows -o line/fs_line.bin
pause