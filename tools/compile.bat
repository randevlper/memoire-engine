shaderc -f vs_cubes.sc --varyingdedf varying.def.sc --type v -platform windows -o vs_cubes.bin
shaderc -f fs_cubes.sc --varyingdedf varying.def.sc --type f -platform windows -o fs_cubes.bin
pause