#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Change to the script directory
cd "$SCRIPT_DIR"

# Set the output executable name
OUTPUT="encryption_tool"

# Delete the previous build if it exists
if [ -f "$OUTPUT" ]; then
    rm "$OUTPUT"
fi

# Find all .cpp files in the current directory and all subdirectories
SRC_FILES=$(find . -name "*.cpp")

# Compile all found .cpp files
g++ -std=c++20 $SRC_FILES -o $OUTPUT

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Build failed."
else
    echo "Build successful! Run with ./$OUTPUT --[encrypt/decrypt] [encryption_type] [encryption_key] [input_file] [output_file]"
fi
