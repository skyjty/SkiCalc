@echo off

@REM cd /d %~dp0..\..

echo Current Path: %cd%

echo Generating Visual Studio 2022 project files...
call .\vendor\bin\premake\premake5.exe vs2022

PAUSE