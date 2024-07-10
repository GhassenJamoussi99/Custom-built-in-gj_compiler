#!/bin/sh
set -e

# Function to clean the project
clean_project() {
    echo "Cleaning the project..."
    make clean
    if [ $? -ne 0 ]; then
        echo "Error: make clean failed."
        exit 1
    fi
    echo "Project cleaned successfully."
}

# Function to build the project
build_project() {
    echo "Building the project..."
    make
    if [ $? -ne 0 ]; then
        echo "Error: make failed."
        exit 1
    fi
    echo "Build completed successfully."
}

# Navigate to the parent directory
cd ..

# Clean and build the project
clean_project
build_project
