@echo off
cmake --version
rd build /s /q
md build
cmake -S src -B build
cmake --build build/

pause
