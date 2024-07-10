#!/bin/sh
set -e

# Function to run the Bison parser setup script
setup_bison() {
    echo "Running the Bison parser setup script..."
    ./setup_parser_bison.sh
    if [ $? -ne 0 ]; then
        echo "Error: Bison setup failed."
        exit 1
    fi
    echo "Bison setup completed successfully."
}

# Function to run the Flex scanner setup script
setup_flex() {
    echo "Running the Flex scanner setup script..."
    ./setup_scanner_flex.sh
    if [ $? -ne 0 ]; then
        echo "Error: Flex setup failed."
        exit 1
    fi
    echo "Flex setup completed successfully."
}

# Run the setup scripts
setup_bison
setup_flex

echo "All setups completed successfully."
