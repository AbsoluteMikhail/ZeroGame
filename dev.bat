@echo off
setlocal
cd /d "%~dp0"

rem =========================================================
rem UE PATH CONFIG (fallback + optional local_config.ini)
rem =========================================================
set "UE_PATH="
set "UE_PATH_SOURCE=hardcoded"
set "CONFIG_FILE=%~dp0Scripts\Batch\local_config.ini"

if exist "%CONFIG_FILE%" (
    for /f "usebackq tokens=1,* delims==" %%A in ("%CONFIG_FILE%") do (
        if /I "%%A"=="UE_PATH" (
            set "UE_PATH=%%B"
            set "UE_PATH_SOURCE=config"
        )
    )
)

if not exist Scripts (
    echo [ERROR] Scripts folder not found!
    pause
    exit /b 1
)

:menu
cls
echo ==========================================
echo            Unreal Dev Tool
echo ==========================================

if "%UE_PATH_SOURCE%"=="config" (
    echo [WARNING] Using UE_PATH from config file!
    echo           ..\Scripts\Batch\local_config.ini
    echo           Make sure it matches your project UE version.
    echo           %UE_PATH%
    echo.
) else (
    echo [INFO] Using fallback UE_PATH:
    echo        %UE_PATH%
    echo.
)

echo 0 - Exit
echo.
echo 1 - Clean project
echo 2 - Generate project files
echo 3 - Build editor target
echo 4 - Run game
echo 5 - Clean + Generate + Build + Run
echo.
echo 6 - Compile all Blueprints
echo.

set /p choice=Select option:

if "%choice%"=="1" (
    echo [INFO] Running CleanProject...
    call Scripts\Batch\CleanProject.bat
    goto menu
)

if "%choice%"=="2" (
    echo [INFO] Generating project files...
    call Scripts\Batch\GenerateProjectFiles.bat
    goto menu
)

if "%choice%"=="3" (
    echo [INFO] Building editor target...
    call Scripts\Batch\BuildEditor.bat
    goto menu
)

if "%choice%"=="4" (
    echo [INFO] Running game...
    call Scripts\Batch\RunAsGame.bat
    goto menu
)

if "%choice%"=="5" (
    echo [INFO] Cleaning project...
    call Scripts\Batch\CleanProject.bat nopause
    if errorlevel 1 goto workflow_failed

    echo [INFO] Generating project files...
    call Scripts\Batch\GenerateProjectFiles.bat nopause
    if errorlevel 1 goto workflow_failed

    echo [INFO] Building editor target...
    call Scripts\Batch\BuildEditor.bat nopause
    if errorlevel 1 goto workflow_failed

    echo [INFO] Running game...
    call Scripts\Batch\RunAsGame.bat nopause
    if errorlevel 1 goto workflow_failed

    goto menu
)

if "%choice%"=="6" (
    echo [INFO] Running Compile All Blueprints...
    call Scripts\Batch\CompileAllBlueprints.bat
    goto menu
)

if "%choice%"=="0" exit /b

if "%choice%"=="" goto menu

echo Invalid option!
timeout /t 1 >nul
goto menu

:workflow_failed
echo.
echo [ERROR] Workflow stopped because one of the steps failed.
echo.
pause
goto menu
