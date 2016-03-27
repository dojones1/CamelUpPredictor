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

testcov: $(ALL_TESTS_RUN) $(RUNCOV)

test: testcov

all: directories software test

docs: 
	$(DOXYGEN) $(DOXYFILE)

docs_clean:
	$(_Q) $(RMRF) $(DOXY_OUT_DIR)


install: all
	@echo you must be root to install

clean: $(ALL_CLEANS) directories_clean docs_clean

