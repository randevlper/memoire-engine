Pushd build
MSBuild.exe goldgame.sln -property:Configuration=Debug
Pushd game\Debug\
game.exe