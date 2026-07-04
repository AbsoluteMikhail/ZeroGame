@echo off
setlocal

rem =========================================================
rem Set your Unreal Engine root folder here.
rem Examples:
rem set "UE_PATH=U:\UNREAL_ENGINE\UE_5.7"
rem set "UE_PATH=U:\UNREAL_ENGINE\UE_4.27"
set "UE_PATH="

if exist "%~dp0local_config.ini" (
    for /f "tokens=1,* delims==" %%A in (%~dp0local_config.ini) do (
        if /I "%%A"=="UE_PATH" set "UE_PATH=%%B"
    )
)

rem Window settings
set "RUN_ARGS=-game -windowed -ResX=1280 -ResY=720 -WinX=100 -WinY=100 -log"

rem =========================================================
rem This script is expected to be placed in:
rem ProjectRoot\Scripts\Batch\RunAsGame.bat
rem =========================================================

cd /d "%~dp0..\.."

echo.
echo ==========================================
echo           Run Unreal Project
echo ==========================================
echo.

set "UPROJECT="

for %%i in (*.uproject) do (
    set "UPROJECT=%%i"
    goto :uproject_found
)

:uproject_found
if not defined UPROJECT (
    echo [ERROR] .uproject not found!
    echo.
    goto :fail
)

if "%UE_PATH%"=="" (
    echo [ERROR] UE_PATH is not set.
    echo Please open this script and set your Unreal Engine root folder at the top.
    echo.
    goto :fail
)

echo [INFO] Found project: %UPROJECT%
echo.

set "EDITOR_EXE="

if exist "%UE_PATH%\Engine\Binaries\Win64\UnrealEditor.exe" (
    set "EDITOR_EXE=%UE_PATH%\Engine\Binaries\Win64\UnrealEditor.exe"
)

if not defined EDITOR_EXE if exist "%UE_PATH%\Engine\Binaries\Win64\UE4Editor.exe" (
    set "EDITOR_EXE=%UE_PATH%\Engine\Binaries\Win64\UE4Editor.exe"
)

if not defined EDITOR_EXE (
    echo [ERROR] Editor executable not found.
    echo Checked:
    echo   %UE_PATH%\Engine\Binaries\Win64\UnrealEditor.exe
    echo   %UE_PATH%\Engine\Binaries\Win64\UE4Editor.exe
    echo.
    goto :fail
)

echo [INFO] Using editor:
echo %EDITOR_EXE%
echo.
echo [INFO] Launch args:
echo %RUN_ARGS%
echo.

start "" "%EDITOR_EXE%" "%cd%\%UPROJECT%" %RUN_ARGS%
if errorlevel 1 goto :fail

echo [DONE] Launch command sent.
echo.

if /I "%1"=="nopause" exit /b 0
pause
exit /b 0

:fail
echo.
echo [ERROR] Failed to launch project.
echo.
if /I "%1"=="nopause" exit /b 1
pause
exit /b 1
