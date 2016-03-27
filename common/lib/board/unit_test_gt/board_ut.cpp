//
//  board_ut.cpp
//  camelUpPredictor
//
//  Created by Donald Jones on 22/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "board.hpp"
#include "gtest/gtest.h"

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>



TEST(Board_init, Positive) {
    Board brd;
    
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        EXPECT_EQ(brd.m_square_vec.at(idx).getLocation(), idx);
    }
    //brd.print();
}

TEST(Board_impediment, Positive) {
    Board brd;
    
    brd.addImpediment(1, oasis, 1);

    brd.addImpediment( 3, swamp, 2);
    EXPECT_EQ(brd.countImpediments(), 2);
    brd.removeImpediment(3);
    EXPECT_EQ(brd.countImpediments(), 1);
    brd.print();
    brd.removeAllImpediments();
    EXPECT_EQ(brd.countImpediments(), 0);
    brd.print();
}

TEST(Board_hasCamelFinished_sq1, Negative) {
    Board brd;
    
    brd.addCamel(1, camelOrange);
    //brd.print();
    EXPECT_EQ(brd.hasCamelFinished(), false);
}

TEST(Board_hasCamelFinished_sq15, Negative) {
    Board brd;
    
    brd.addCamel(15, camelOrange);
    //brd.print();
    EXPECT_EQ(brd.hasCamelFinished(), false);
}

TEST(Board_hasCamelFinished_sq16, Positive) {
    Board brd;
    
    brd.addCamel(16, camelOrange);
    //brd.print();
    EXPECT_EQ(brd.hasCamelFinished(), true);
}
// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
