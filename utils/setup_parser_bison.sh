#!/bin/sh
set -e

# Navigate to the parent directory
cd ..

# Run Bison to generate the parser
echo "Running Bison to generate the parser..."
bison --defines=include/token.h -Wcounterexamples --output=tools/parser.cpp -v -d -t assets/parser.bison
if [ $? -ne 0 ]; then
    echo "Error: Bison failed to generate the parser."
    exit 1
fi
echo "Bison completed successfully."
