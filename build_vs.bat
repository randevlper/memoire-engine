for /f "usebackq tokens=*" %%i in (`vswhere -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
  Pushd build
  "%%i" goldgame.sln /t:game /p:Configuration=%CONFIG%
  if not exist game\%CONFIG%\assets mkdir game\%CONFIG%\assets
  xcopy /s /y ..\game\assets  game\%CONFIG%\assets
  Pushd game\%CONFIG%\
  game.exe
  exit /b !errorlevel!
)