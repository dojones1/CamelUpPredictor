include build/makefile.rules


##########################
# Pull in build targets from the system
# Thirdparty libraries first
include $(THIRDPARTY_DIR)/makefile.inc
include $(COMMON_LIB_DIR)/makefile.inc
include $(PROCESS_DIR)/makefile.inc


###########################

software: directories $(ALL_LIBS) $(ALL_BINS)

alltests: directories $(ALL_TESTS)

test: $(ALL_TESTS_RUN)

all: directories software test
	@echo "Valgrind: $(VALGRIND)"
	@echo "CCACHE: $(CCACHE)"
	
install: all
	@echo you must be root to install

clean: $(ALL_CLEANS) directories_clean
