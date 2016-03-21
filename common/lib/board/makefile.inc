include $(BOARD_DIR)/unit_test_gt/makefile.inc

BOARD_LIB_CPP_SRC = $(wildcard $(BOARD_DIR)/src/*.cpp)
BOARD_LIB_CPP_FLAGS = -I$(BOARD_DIR)/public_inc
BOARD_LIB_LINKER_FLAGS =
$(eval $(call OSX_LIB,libboard,libboard,,,$(BOARD_LIB_CPP_SRC),$(BOARD_LIB_CPP_FLAGS)))
