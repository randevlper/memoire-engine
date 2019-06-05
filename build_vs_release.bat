Pushd build
MSBuild.exe goldgame.sln -property:Configuration=Release
Pushd game\Release\
game.exe