@echo off

call cl >nul 2>nul

if not %errorlevel% == 0 (
    echo COMPILE-INFO: Setting up cl compiler.
    call vcvarsall.bat x64 >nul 2>nul
)

if not %errorlevel% == 0 (
    echo COMPILE-INFO: cl compiler is required. Install Microsoft Visual Studio 2022 and make sure vcvarsall.bat is in your PATH
)

if exist build call rmdir /s /q build

mkdir build

call cl code\*.c /Fe:build\ray_tracer.exe >nul 2>nul

call del *.obj

call build\ray_tracer.exe
