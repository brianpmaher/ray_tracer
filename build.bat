@echo off

call cl >nul 2>nul

if not %errorlevel% == 0 (
    echo COMPILE-INFO: Setting up cl compiler.
    echo COMPILE-INFO: Future build runs will be faster.
    call vcvarsall.bat x64 >nul 2>nul
)

if not %errorlevel% == 0 (
    echo COMPILE-ERROR: cl compiler is required.
    echo COMPILE-ERROR: Install Microsoft Visual Studio 2022 and make sure vcvarsall.bat is in your PATH.
    exit /b 1
)

if exist build call rmdir /s /q build

mkdir build

call cl /nologo /Wall /Fe:build\ray_tracer.exe /std:c11 code\*.c 

call del *.obj

call build\ray_tracer.exe
