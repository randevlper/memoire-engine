shaderc -f sprite/vs_sprite.sc --varyingdedf sprite/varying.def.sc --type v -platform windows -o sprite/vs_sprite.bin
shaderc -f sprite/fs_sprite.sc --varyingdedf sprite/varying.def.sc --type f -platform windows -o sprite/fs_sprite.bin
pause