if not exist build mkdir build
Pushd build
cmake ../ %PAREM%
Pushd ..
if not exist "build\goldgame.sln" exit
for /f "usebackq tokens=1* delims=: " %%i in (`vswhere.exe -latest -requires Microsoft.VisualStudio.Workload.NativeDesktop`) do (
	if /i "%%i"=="installationPath" (
	"%%j\Common7\IDE\devenv.exe" "build\goldgame.sln"
	exit
	)
)