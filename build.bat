@echo off

rem ////////////////////////////////////////////////////////////////////////////////
rem                                    Config
rem ////////////////////////////////////////////////////////////////////////////////

set runUnitTests=0
set runRayTracer=0
set debugBuild=0

:configLoop
if "%1"=="" goto endConfigLoop
if "%1"=="-t" set runUnitTests=1
if "%1"=="-r" set runRayTracer=1
if "%1"=="-d" set debugBuild=1
shift
goto configLoop
:endConfigLoop

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

if exist _Build call rmdir /s /q _Build

mkdir _Build

set defines=
if %runUnitTests% == 1 set defines=%defines% /DRUN_UNIT_TESTS
if %runRayTracer% == 1 set defines=%defines% /DRUN_RAY_TRACER

set flags=/nologo /W3 /Fe:_Build\ray_tracer.exe /std:c11
if %debugBuild% == 1 (
    set flags=%flags% /Zi /Od
) else (
    set flags=%flags% /O2
)

call cl %flags% Sources\*.c %defines%

move *.pdb _Build >nul 2>nul

call del *.obj

if %errorlevel% == 0 (
    if %debugBuild% == 1 (
        call remedybg debug.rdbg
    ) else (
        call _Build\ray_tracer.exe
    )
)
