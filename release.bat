@echo off
set fd=release
if exist %fd% (
	echo.
	echo ### Delete old build files
    rd %fd% /s/q
)
if not exist %fd% (
	echo.
	echo ### Make Directory release/
	md %fd%
)
echo.
echo.
echo ### CMake from source code...
cmake -S src -B %fd%
echo.
echo.
echo ### Building from make files...
cmake --build %fd%/ --config Release

ren %fd% tmp
md %fd%
xcopy "tmp\Release\*.*" %fd% /s/h/e/k/f/c
xcopy "opencv\x64\vc15\bin\opencv_world454.dll" %fd% /s/h/e/k/f/c
xcopy "res\*.*" "%fd%\res\" /s/h/e/k/f/c
rd tmp /s/q

pause
