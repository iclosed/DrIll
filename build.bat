@echo off
set fd=build
cmake --version
if exist %fd% (
	echo ### Delete old build files
    rd %fd% /s /q
)
md %fd%
echo #
echo ##
echo ### CMake from source code...
cmake -S src -B %fd%
echo #
echo ##
echo ### Building from make files...
cmake --build %fd%/

pause
