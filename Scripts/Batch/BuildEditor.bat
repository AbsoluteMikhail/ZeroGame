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

set "BUILD_CONFIG=Development"
set "BUILD_PLATFORM=Win64"

rem =========================================================
rem This script is expected to be placed in:
rem ProjectRoot\Scripts\Batch\BuildEditor.bat
rem =========================================================

cd /d "%~dp0..\.."

echo.
echo ==========================================
echo        Build Unreal Editor Target
echo ==========================================
echo.

set "UPROJECT="
set "PROJECT_NAME="

for %%i in (*.uproject) do (
    set "UPROJECT=%%i"
    set "PROJECT_NAME=%%~ni"
    goto :uproject_found
)

:uproject_found
if not defined UPROJECT (
    echo [ERROR] .uproject not found in:
    echo %cd%
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
echo [INFO] Project name: %PROJECT_NAME%
echo [INFO] Target: %PROJECT_NAME%Editor
echo [INFO] Build config: %BUILD_CONFIG%
echo [INFO] Build platform: %BUILD_PLATFORM%
echo.

set "UBT_PATH="
set "UBT_PATH_UE5=%UE_PATH%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
set "UBT_PATH_UE4=%UE_PATH%\Engine\Binaries\DotNET\UnrealBuildTool.exe"

if exist "%UBT_PATH_UE5%" set "UBT_PATH=%UBT_PATH_UE5%"
if not defined UBT_PATH if exist "%UBT_PATH_UE4%" set "UBT_PATH=%UBT_PATH_UE4%"

if not defined UBT_PATH (
    echo [ERROR] UnrealBuildTool not found.
    echo Checked:
    echo   %UBT_PATH_UE5%
    echo   %UBT_PATH_UE4%
    echo.
    goto :fail
)

echo [INFO] Using UnrealBuildTool:
echo %UBT_PATH%
echo.

call "%UBT_PATH%" %PROJECT_NAME%Editor %BUILD_PLATFORM% %BUILD_CONFIG% -Project="%cd%\%UPROJECT%" -WaitMutex -NoHotReloadFromIDE
if errorlevel 1 goto :fail

echo.
echo [DONE] Editor target built successfully.
echo.

if /I "%1"=="nopause" exit /b 0
pause
exit /b 0

:fail
echo.
echo [ERROR] Build failed.
echo.
if /I "%1"=="nopause" exit /b 1
pause
exit /b 1
