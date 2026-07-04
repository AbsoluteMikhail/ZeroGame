@echo off
setlocal

rem =========================================================
rem Set your Unreal Engine root folder here if needed.
rem Leave empty to use UnrealVersionSelector first.
rem Examples:
rem set "UE_PATH=U:\UNREAL_ENGINE\UE_5.7"
rem set "UE_PATH=U:\UNREAL_ENGINE\UE_4.27"
set "UE_PATH="

if exist "%~dp0local_config.ini" (
    for /f "tokens=1,* delims==" %%A in (%~dp0local_config.ini) do (
        if /I "%%A"=="UE_PATH" set "UE_PATH=%%B"
    )
)

rem =========================================================
rem This script is expected to be placed in:
rem ProjectRoot\Scripts\Batch\GenerateProjectFiles.bat
rem =========================================================

cd /d "%~dp0..\.."

echo.
echo ==========================================
echo   Generate Unreal Project Files
echo ==========================================
echo.

set "UPROJECT="

for %%i in (*.uproject) do (
    set "UPROJECT=%%i"
    goto :uproject_found
)

:uproject_found
if not defined UPROJECT (
    echo [ERROR] .uproject not found in:
    echo %cd%
    echo.
    goto :fail
)

echo [INFO] Found project: %UPROJECT%
echo.

rem Method 1: UnrealVersionSelector
set "UVS=%ProgramFiles(x86)%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"

if exist "%UVS%" (
    echo [INFO] Using UnrealVersionSelector
    "%UVS%" /projectfiles "%cd%\%UPROJECT%"
    if errorlevel 1 goto :fail
    goto :success
)

echo [WARN] UnrealVersionSelector not found.
echo.

rem Method 2: Manual UE_PATH + UnrealBuildTool
if "%UE_PATH%"=="" (
    echo [ERROR] UE_PATH is not set.
    echo Please open this script and set your Unreal Engine root folder at the top.
    echo.
    goto :fail
)

echo [INFO] Using Unreal Engine root:
echo %UE_PATH%
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

call "%UBT_PATH%" -projectfiles -project="%cd%\%UPROJECT%" -game -engine
if errorlevel 1 goto :fail

:success
echo.
echo [DONE] Project files generated successfully.
echo.

if /I "%1"=="nopause" exit /b 0
pause
exit /b 0

:fail
echo.
echo [ERROR] Project files generation failed.
echo.
if /I "%1"=="nopause" exit /b 1
pause
exit /b 1
