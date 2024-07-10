#!/bin/bash

# Directories and files
TEST_DIR_3="bminor_tests/standard_tests/codegen"
GJ_COMPILER="./gj_compiler"
ASM_FILE="asm.s"
ASM_OUT="asm.out"
TEST_CASES_FILE="test_cases.json"

# Function to run the tests
run_tests() {
    local test_cases_file="$1"
    
    # Read the list of test files from JSON
    local json_data
    json_data=$(<"$test_cases_file")
    local test_files
    test_files=$(echo "$json_data" | jq -r '.tests[] | .file')

    for TEST_FILE in $test_files; do
        echo -e "\n############## Compiling $TEST_FILE ####################"
        # Compile with gj_compiler
        $GJ_COMPILER "$TEST_DIR_3/$TEST_FILE"

        # Check return status
        if [ $? -ne 0 ]; then
            echo -e "\e[31mError compiling $TEST_FILE in $TEST_DIR_3. Exiting.\e[0m"
            exit 1
        fi

        # Copy asm.s to test directory
        cp $ASM_FILE "$TEST_DIR_3/$TEST_FILE.s"

        # Optional: Copy other generated files if needed
        cp ast.dot "$TEST_DIR_3/$TEST_FILE.dot"
        cp ast_optimized.dot "$TEST_DIR_3/$TEST_FILE_optimized.dot"

        # Generate PDF from dot files (optional)
        dot -Tpdf ast.dot -o "$TEST_DIR_3/$TEST_FILE"_dot.pdf 
        dot -Tpdf ast_optimized.dot -o "$TEST_DIR_3/$TEST_FILE"_optimized_dot.pdf

        # Compile asm.s to asm.out
        gcc -o $ASM_OUT $ASM_FILE -no-pie -fPIE

        # Check compilation success
        if [ $? -ne 0 ]; then
            echo -e "\e[31mError compiling $ASM_FILE to $ASM_OUT in $TEST_DIR_3. Exiting.\e[0m"
            exit 1
        fi

        # Run asm.out and capture output
        OUTPUT=$(./$ASM_OUT)
        ASM_EXIT_CODE=$?

        # Retrieve expected output and exit code from JSON using jq
        EXPECTED_OUTPUT=$(echo "$json_data" | jq -r ".tests[] | select(.file == \"$TEST_FILE\") | .expected_output")
        EXPECTED_EXIT_CODE=$(echo "$json_data" | jq -r ".tests[] | select(.file == \"$TEST_FILE\") | .expected_exit_code")
        
        # Check if expected values are empty
        if [ -z "$EXPECTED_EXIT_CODE" ]; then
            echo -e "\e[31mError: Expected values not found for $TEST_FILE. Exiting.\e[0m"
            exit 1
        fi

        # Compare output with expected
        if [ "$OUTPUT" != "$EXPECTED_OUTPUT" ]; then
            echo -e "\e[31mError: Test $TEST_FILE failed. Expected output: '$EXPECTED_OUTPUT', Actual output: '$OUTPUT'\e[0m"
            exit 1
        fi

        # Compare exit code with expected
        if [ "$ASM_EXIT_CODE" -ne "$EXPECTED_EXIT_CODE" ]; then
            echo -e "\e[31mError: Test $TEST_FILE failed. Expected exit code: $EXPECTED_EXIT_CODE, Actual exit code: $ASM_EXIT_CODE\e[0m"
            exit 1
        fi

        echo -e "\e[32mTest $TEST_FILE successful.\e[0m"
        echo "Expected stdout output: '$EXPECTED_OUTPUT', Actual stdout output: '$OUTPUT'"
        echo "Expected exit code: $EXPECTED_EXIT_CODE, Actual exit code: $ASM_EXIT_CODE"
        echo -e "\e[32mDone\e[0m"
    done
}

# Run tests using test_cases.json
run_tests "$TEST_CASES_FILE"
