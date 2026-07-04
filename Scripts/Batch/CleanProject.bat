@echo off
setlocal

rem =========================================================
rem This script is expected to be placed in:
rem ProjectRoot\Scripts\Batch\CleanProject.bat
rem =========================================================

cd /d "%~dp0..\.."

echo.
echo ==========================================
echo           Clean Unreal Project
echo ==========================================
echo.

rem =========================
rem Visual Studio
rem =========================
rd /S /Q .vs 2>nul
del /Q *.sln 2>nul

rem =========================
rem Visual Studio Code
rem =========================
rd /S /Q .vscode 2>nul
del /Q *.code-workspace 2>nul
del /Q .vsconfig 2>nul

rem =========================
rem Rider
rem =========================
rd /S /Q .idea 2>nul

rem =========================
rem Unreal Engine
rem =========================

rem Binaries - compiled binaries
rd /S /Q Binaries 2>nul

rem Build - build settings
rd /S /Q Build 2>nul

rem Intermediate - temporary files generated when you compile your code
rd /S /Q Intermediate 2>nul

rem Saved - local logs, config, autosaves, screenshots (disabled intentionally)
rem rd /S /Q Saved 2>nul

rem DerivedDataCache - local cache
rd /S /Q DerivedDataCache 2>nul

echo [DONE] Project cleanup completed.
echo.

if /I "%1"=="nopause" exit /b 0
pause
exit /b 0
