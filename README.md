# Custom built-in gj_compiler

## Introduction
This project is an implementation of a custom compiler in C++.

##  Prerequisites
Before launching the program, ensure you have the following tools installed:
- **Bison** - a parser generator that is part of the GNU Project.
- **Flex** - a tool for generating scanners.

### Installing Bison and Flex
Bison and Flex can be installed on Ubuntu/Debian-based systems using the following command:

```bash
sudo apt-get update
sudo apt-get install bison flex
```

## Development Environment
This development environment consists of the following key components:
- **Makefile**: Used for building the project.
- **Source Code**: Located in the `src` and `include` directories, containing the C++ implementation of the compiler.
- **Assets**: Contains `parser.bison` and `scanner.flex` files.
- **Build**: Directory for build artifacts.
- **Tests**: Various test cases organized in subdirectories within `bminor_tests`.
- **Scripts**: Includes `setup_and_build.sh` for compiling and `run_tests.sh` for running tests.
- **Documentation**: Additional documentation in the `doc` directory.

## Usage
To compile the program, run the following command in the root directory of the project:
```
./setup_and_build.sh 
```

This will compile the project and generate an executable file called `gj_compiler`. To run the program, simply execute the following command:

```
./run_tests.sh
```

## Resources
- [Compiler Examples Repository](https://github.com/dthain/compilerbook-examples/tree/master): A variety of compiler examples on GitHub based on [Compiler Book](http://compilerbook.org/).
- [Compiler Explorer](https://godbolt.org/): Interactively explore and test compiler outputs online.

## Done by
```
   Ghassen Jamoussi
```
