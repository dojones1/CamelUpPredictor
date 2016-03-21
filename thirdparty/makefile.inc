

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = $(THIRDPARTY_DIR)/googletest/googletest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
GTEST_CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
GTEST_CXXFLAGS += -g -O0 -Wall -Wextra -pthread

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

define COMMON_GTEST_LIB
# 1 - target

            
# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
$$($(1)_UT_OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
	@ echo "\033[0;34m [ $(1)_UT_OBJ_C: $$@] \033[m"
	$(_Q) $(MKDIR) `dirname $$@`
	$(_Q) $(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc  -o $$@ 

$$($(1)_UT_OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
	@ echo "\033[0;34m [ $(1)_UT_OBJ_C++: $$@] \033[m"
	$(_Q) $(MKDIR) `dirname $$@`
	$(_Q) $(CXX) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) $(GTEST_CXXFLAGS) -c \
	        $(GTEST_DIR)/src/gtest_main.cc  -o $$@ 

$$($(1)_UT_OBJ_DIR)/gtest.a : $$($(1)_UT_OBJ_DIR)/gtest-all.o
	@ echo "\033[0;34m [ $(1)_UT_AR: $$@] \033[m"
	$(_Q) $(AR) $(ARFLAGS) $$@ $$^

$$($(1)_UT_OBJ_DIR)/gtest_main.a : $$($(1)_UT_OBJ_DIR)/gtest-all.o $$($(1)_UT_OBJ_DIR)/gtest_main.o
	@ echo "\033[0;34m [ $(1)_UT_AR: $$@] \033[m"
	$(_Q) $(AR) $(ARFLAGS) $$@ $$^
	
$(1)_googletest:$$($(1)_UT_OBJ_DIR)/gtest_main.a

$(1)_googletest_clean: 
	$(_Q) $(RM) $$($(1)_UT_OBJ_DIR)/gtest.a $$($(1)_UT_OBJ_DIR)/gtest_main.a *.o
	
ALL_CLEANS += $(1)_googletest_clean
THIRDPARTY_DEPS += $(1)_googletest
endef

$(eval $(call COMMON_GTEST_LIB,OSX));

thirdparty: $(THIRDPARTY_DEPS)