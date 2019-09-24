shaderc -f cube/vs_cubes.sc --varyingdedf cube/varying.def.sc --type v -platform windows -p ps_4_0 -o cube/vs_cubes.bin -O 0 --debug
shaderc -f cube/fs_cubes.sc --varyingdedf cube/varying.def.sc --type f -platform windows -p ps_4_0 -o cube/fs_cubes.bin -O 0 --debug
pause