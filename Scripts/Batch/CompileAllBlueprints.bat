@echo off
setlocal

set "UE_PATH="
set "UE_PATH_SOURCE=hardcoded fallback"
set "CONFIG_FILE=%~dp0local_config.ini"

if exist "%CONFIG_FILE%" (
    for /f "usebackq tokens=1,* delims==" %%A in ("%CONFIG_FILE%") do (
        if /I "%%A"=="UE_PATH" (
            set "UE_PATH=%%B"
            set "UE_PATH_SOURCE=local_config.ini"
        )
    )
)

cd /d "%~dp0..\.."

echo.
echo ==========================================
echo        Compile All Blueprints
echo ==========================================
echo.

if "%UE_PATH_SOURCE%"=="local_config.ini" (
    echo [WARNING] UE_PATH loaded from config file.
    echo           Make sure it matches your project UE version.
    echo           %UE_PATH%
    echo.
) else (
    echo [INFO] Using fallback UE_PATH:
    echo        %UE_PATH%
    echo.
)

if "%UE_PATH%"=="" goto :fail

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

set "EDITOR_CMD_EXE="

if exist "%UE_PATH%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" (
    set "EDITOR_CMD_EXE=%UE_PATH%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
)

if not defined EDITOR_CMD_EXE if exist "%UE_PATH%\Engine\Binaries\Win64\UE4Editor-Cmd.exe" (
    set "EDITOR_CMD_EXE=%UE_PATH%\Engine\Binaries\Win64\UE4Editor-Cmd.exe"
)

if not defined EDITOR_CMD_EXE (
    echo [ERROR] Commandlet executable not found.
    goto :fail
)

echo [INFO] Using commandlet executable:
echo        %EDITOR_CMD_EXE%
echo.

call "%EDITOR_CMD_EXE%" "%cd%\%UPROJECT%" -run=CompileAllBlueprints -unattended -nop4 -nosplash -log
if errorlevel 1 goto :fail

echo [DONE] Blueprint compilation finished successfully.
echo.
if /I "%1"=="nopause" exit /b 0
pause
exit /b 0

:fail
echo [ERROR] Blueprint compilation failed.
echo.
if /I "%1"=="nopause" exit /b 1
pause
exit /b 1
