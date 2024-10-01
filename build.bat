@echo off

rem Get the directory of the batch file
set "SCRIPT_DIR=%~dp0"

rem Change to the script directory
cd /d "%SCRIPT_DIR%"

rem Set the output executable name
set OUTPUT=encryption_tool.exe

rem Delete the previous build if it exists
if exist %OUTPUT% (
    del %OUTPUT%
)

rem Compile all .cpp files in the directory and the util directory
g++ *.cpp util\*.cpp -o %OUTPUT%

rem Check if the compilation was successful
if %errorlevel% neq 0 (
    echo Build failed.
) else (
    echo Build successful! Run with %OUTPUT% [encrypt/decrypt] [input_file] [output_file]
)
