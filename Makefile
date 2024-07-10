#######################################################
#define name of the executable
EXECUTABLE_NAME = gj_compiler
########################################################

########################################################
#####################  INCLUDES  #######################
########################################################
include sources.mk

########################################################
####################  VARIABLES  #######################
########################################################
# "?=" means set by default

ENABLE_WARNINGS ?= 1
WARNINGS_AS_ERRORS ?= 0
CPP_COMPILER ?= g++ # gcc, clang++
CPP_STANDARD ?= c++2a # c++11, c++14, c++17, c++20
MKDIR_P = mkdir -p $(BUILD_DIR)
MV_EX = mv build/$(EXECUTABLE_NAME)* .
LDLIBS = #..

CPP_COMPILER_FLAGS = -fprofile-arcs -ftest-coverage -g -O0 -std=$(CPP_STANDARD)

ifeq ($(ENABLE_WARNINGS),1)
CPP_COMPILER_FLAGS += -Wall -Wextra -Wpedantic -Wconversion
endif

ifeq ($(WARNINGS_AS_ERRORS),1)
CPP_COMPILER_FLAGS += -Werror
endif

CPP_COMPILER_CALL = $(CPP_COMPILER) $(CPP_COMPILER_FLAGS)

# Find all cpp sources
CPP_SOURCES = $(wildcard $(addsuffix /*.cpp,$(SOURCE_DIR)))
CPP_OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(CPP_SOURCES)))

########################################################
####################  PSEUDO TARGETS  ##################
########################################################
all: setup_build_dir build move_executable
build: $(BUILD_DIR)/$(EXECUTABLE_NAME)

########################################################
#####################  TARGETS  ########################
########################################################
#targetname : dependencies
setup_build_dir:
	$(MKDIR_P)

move_executable:
	$(MV_EX)

# OBJECT FILES to an EXECUTABLE : %.o -> %.exe/out
TARGET_DEPS = $(CPP_OBJECTS) $(CC_OBJECTS) 
$(BUILD_DIR)/$(EXECUTABLE_NAME): $(TARGET_DEPS)
	$(CPP_COMPILER_CALL) $^ $(LDLIBS) -o $@

execute:
	.$(BUILD_DIR)/$(EXECUTABLE_NAME)

########################################################
#####################  PATTERNS  #######################
########################################################
vpath %.cpp $(SOURCE_DIR)
$(BUILD_DIR)/%.o: %.cpp
	$(CPP_COMPILER_CALL) $(INCLUDE_DIR) -c $< -o $@
#create a target bzw object file for the libraries

########################################################
####################### PHONY  #########################
########################################################
# -rf will remove the directory if it's present.
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE_NAME)*
