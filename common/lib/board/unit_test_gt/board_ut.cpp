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
    brd.print();
}

TEST(Board_impediment, Positive) {
    Board brd;
    
    brd.addImpediment(1, oasis, 1);

    brd.addImpediment( 3, swamp, 2);
    EXPECT_EQ(brd.countImpediments(), 2);
    brd.removeImpediment(3);
    EXPECT_EQ(brd.countImpediments(), 1);
    //brd.print();
    brd.removeAllImpediments();
    EXPECT_EQ(brd.countImpediments(), 0);
    //brd.print();
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

//! Need to identify which camel is leading or not.
TEST(Board_camelPlaces_0, Positive) {
    Board brd;
    EXPECT_EQ(brd.whichCamelIsLeading(), unknownCamel);
    EXPECT_EQ(brd.whichCamelIsSecond(), unknownCamel);
    EXPECT_EQ(brd.whichCamelIsLast(), unknownCamel);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelPlaces_1, Positive) {
    Board brd;
    
    brd.addCamel(0, camelOrange);
    brd.addCamel(0, camelGreen);
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
    EXPECT_EQ(brd.whichCamelIsLast(), camelOrange);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelPlaces_2, Positive) {
    Board brd;
    
    brd.addCamel(0, camelOrange);
    brd.addCamel(0, camelGreen);
    brd.addCamel(0, camelYellow);
    brd.addCamel(1, camelBlue);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
    EXPECT_EQ(brd.whichCamelIsLast(), camelOrange);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelPlaces_3, Positive) {
    Board brd;
    
    brd.addCamel(0, camelOrange);
    brd.addCamel(0, camelGreen);
    brd.addCamel(1, camelYellow);
    brd.addCamel(1, camelBlue);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
    EXPECT_EQ(brd.whichCamelIsLast(), camelOrange);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelPlaces_4, Positive) {
    Board brd;
    
    brd.addCamel(0, camelOrange);
    brd.addCamel(1, camelGreen);
    brd.addCamel(1, camelYellow);
    brd.addCamel(1, camelBlue);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
    EXPECT_EQ(brd.whichCamelIsLast(), camelOrange);
}


TEST(Board_camelMovesNoImpediment_0, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    //brd.print();
    
    brd.moveCamel(camelBlue,1);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
}

TEST(Board_camelMovesNoImpediment_0a, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    //brd.print();
    
    brd.moveCamel(camelYellow,1);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
}

TEST(Board_camelMovesNoImpediment_0b, Positive) {
    Board brd;
    brd.addCamel(0, camelOrange);
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    //brd.print();
    
    brd.moveCamel(camelYellow,1);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
}

TEST(Board_camelMovesSwampImpediment_1, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addImpediment(1,swamp,0);
    //brd.print();
    
    brd.moveCamel(camelBlue,1);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelYellow);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelBlue);
}

TEST(Board_camelMovesSwampImpediment_2, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addCamel(1, camelOrange);
    brd.addImpediment(2,swamp,2);
    //brd.print();
    
    EXPECT_EQ(brd.moveCamel(camelBlue,2),2);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelOrange);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelBlue);
}

TEST(Board_camelMovesSwampImpediment_3, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addCamel(0, camelGreen);
    brd.addCamel(1, camelOrange);
    brd.addImpediment(2,swamp,4);
    //brd.print();
    
    EXPECT_EQ(brd.moveCamel(camelBlue,2), 4);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelOrange);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelGreen);
    EXPECT_EQ(brd.whichCamelIsLast(), camelYellow);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelMovesOasisImpediment_1, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addImpediment(1,oasis,0);
    //brd.print();
    
    EXPECT_EQ(brd.moveCamel(camelBlue,1),0);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelMovesOasisImpediment_2, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addImpediment(1,oasis,3);
    //brd.print();
    
    EXPECT_EQ(brd.moveCamel(camelBlue,1),3);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelYellow);
}

//! Need to identify which camel is leading or not.
TEST(Board_camelMovesOasisImpediment_3, Positive) {
    Board brd;
    brd.addCamel(0, camelYellow);
    brd.addCamel(0, camelBlue);
    brd.addCamel(2, camelOrange);
    brd.addImpediment(1,oasis,5);
    EXPECT_EQ(brd.whichCamelIsLeading(), camelOrange);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelBlue);
    //brd.print();
    
    EXPECT_EQ(brd.moveCamel(camelBlue,1),5);
    //brd.print();
    EXPECT_EQ(brd.whichCamelIsLeading(), camelBlue);
    EXPECT_EQ(brd.whichCamelIsSecond(), camelOrange);
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
