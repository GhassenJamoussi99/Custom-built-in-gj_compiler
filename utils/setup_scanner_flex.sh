#!/bin/sh
set -e

# Navigate to the parent directory
cd ..

# Run Flex to generate the scanner
echo "Running Flex to generate the scanner..."
flex -o tools/flex.cpp assets/scanner.flex
if [ $? -ne 0 ]; then
    echo "Error: Flex failed to generate the scanner."
    exit 1
fi
echo "Flex completed successfully."
