BOARD_UT_CPP_SRC = $(wildcard $(BOARD_DIR)/unit_test_gt/*.cpp) $(wildcard $(BOARD_DIR)/src/*.cpp) build/OSX_UT/obj/gtest_main.a
BOARD_UT_CPP_FLAGS = -I$(BOARD_DIR)/public_inc -I$(GTEST_DIR)/include
BOARD_LINKER_FLAGS = -lpthread
$(eval $(call OSX_UT,board_ut,board_ut,,,$(BOARD_UT_CPP_SRC),$(BOARD_UT_CPP_FLAGS), $(BOARD_UT_LINKER_FLAGS)))


# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

# sample1.o : $(USER_DIR)/sample1.cc $(USER_DIR)/sample1.h $(GTEST_HEADERS)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.cc

# sample1_unittest.o : $(USER_DIR)/sample1_unittest.cc \
#                      $(USER_DIR)/sample1.h $(GTEST_HEADERS)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1_unittest.cc

# sample1_unittest : sample1.o sample1_unittest.o gtest_main.a
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@