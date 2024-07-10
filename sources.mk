############################################################
####################  DIRECTORIES  #########################
############################################################

# Add your include paths to this variable
INCLUDE = include						\
		  include/ast					\
		  tools/						\
		  backend/

INCLUDE_DIR = $(addprefix -I,$(INCLUDE))

# Add your source paths to this variable
SOURCE_DIR = src/						\
			 src/ast/					\
			 tools/						\
			 backend/					

# Add your build path to this variable
BUILD_DIR = build
