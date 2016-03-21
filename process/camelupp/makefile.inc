CAMELUPP_CPP_SRC = $(wildcard $(CAMELUPP_DIR)/*.cpp)
CAMELUPP_INCLUDES = -I$(CAMELUPP_DIR)/public_inc
CAMELUPP_LINKER_FLAGS = -lboard

# 1 is the name of the make file target
# 2 is the name of the binary
# 3 is the list of c files
# 4 is the c flags
# 5 is the list of c++ files
# 6 is the c++ flags
$(eval $(call OSX_BIN, camelupp,camelupp,,,$(CAMELUPP_CPP_SRC),$(CAMELUPP_INCLUDES),$(CAMELUPP_LINKER_FLAGS))