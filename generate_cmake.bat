if not exist build mkdir build
Pushd build
cmake ../ %PAREM%
Pushd ..
pause
if not exist "build\memoire-enginee.sln" exit
for /f "usebackq tokens=1* delims=: " %%i in (`vswhere.exe -latest -requires Microsoft.VisualStudio.Workload.NativeDesktop`) do (
	if /i "%%i"=="installationPath" (
	"%%j\Common7\IDE\devenv.exe" "build\memoire-engine.sln"
	exit
	)
)
