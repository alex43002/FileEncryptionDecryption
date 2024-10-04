@echo off
setlocal EnableDelayedExpansion

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

rem Initialize an empty variable to hold all source files
set "SRC_FILES="

rem Recursively find all .cpp files in the current directory and all subdirectories
for /R %%f in (*.cpp) do (
    set "SRC_FILES=!SRC_FILES! %%f"
)

rem Compile all found .cpp files
g++ %SRC_FILES% -o %OUTPUT%

rem Check if the compilation was successful
if %errorlevel% neq 0 (
    echo Build failed.
) else (
    echo Build successful! Run with %OUTPUT% [encrypt/decrypt] [input_file] [output_file]
)

endlocal