@echo off
echo Current Path: %cd%
echo This will delete Visual Studio build files and intermediate files.
echo.
echo WARNING: This will remove bin/, bin-int/, and *.sln/vcxproj/etc files outside vendor/.
echo.

set /p confirm=Do you want to continue? [Y/N]: 
if /I not "%confirm%"=="Y" (
    echo Operation cancelled.
    goto :eof
)

echo Cleaning old Visual Studio project files...

REM 删除 bin 和 bin-int 目录
if exist bin (
    echo Deleting bin directory...
    rmdir /s /q bin
)
if exist bin-int (
    echo Deleting bin-int directory...
    rmdir /s /q bin-int
)

REM 删除指定类型文件，但跳过 vendor 目录
for %%f in (sln vcxproj vcxproj.filters vcxproj.user opensdf sdf suo ipch) do (
    for /r %%i in (*.%%f) do (
        echo %%i | findstr /i "\\vendor\\" >nul
        if errorlevel 1 (
            echo Deleting %%i
            del /f /q "%%i"
        ) else (
            echo Skipping vendor: %%i
        )
    )
)

REM 删除 *.vcxproj.*.user，但跳过 vendor 目录
for /r %%i in (*.vcxproj.*.user) do (
    echo %%i | findstr /i "\\vendor\\" >nul
    if errorlevel 1 (
        echo Deleting %%i
        del /f /q "%%i"
    ) else (
        echo Skipping vendor: %%i
    )
)

echo Clean complete.
pause