@echo off
set fd=release
cmake --version
if exist %fd% (
	echo.
	echo ### Delete old build files
    rd %fd% /s /q
)
if not exist %fd% (
	echo.
	echo ### Make Directory build/
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

pause
