@echo off

rem ////////////////////////////////////////////////////////////////////////////////
rem                                    Config
rem ////////////////////////////////////////////////////////////////////////////////

set runUnitTests=1
set debugBuild=0

rem ////////////////////////////////////////////////////////////////////////////////

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

set defines=
if %runUnitTests% == 1 set defines=/DRUN_UNIT_TESTS

set flags=/nologo /W3 /Fe:build\ray_tracer.exe /std:c11
if %debugBuild% == 1 (
    set flags=%flags% /Zi /Od
) else (
    set flags=%flags% /O2
)

call cl %flags% code\*.c %defines%

move *.pdb build >nul 2>nul

call del *.obj

if %errorlevel% == 0 (
    if %debugBuild% == 1 (
        call remedybg debug.rdbg
    ) else (
        call build\ray_tracer.exe
    )
)
