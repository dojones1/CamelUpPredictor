//
//  gameState_ut.cpp
//  camelUpPredictor
//
//  Created by Donald Jones on 29/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "gameState.hpp"
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

TEST(GameState, init) {
    gameState gs;
    
    gs.print(); // to ensure that the code is executed
}

TEST(GameState, addCamel) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.addImpediment(2, imp_oasis, 4);
    
    gs.printMinimal(); // to ensure that the code is executed
    gs.removeAllImpediments();
}

TEST(GameState, diceAlreadyRolled_invalidCamel) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    
    try{
        gs.diceAlreadyRolled(camelBlue, 1);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Camel was not on the board"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, diceAlreadyRolled_invalidDice_0) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.diceAlreadyRolled(camelOrange, 0);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Invalid dice roll"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, diceAlreadyRolled_invalidDice_4) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.diceAlreadyRolled(camelOrange, 4);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Invalid dice roll"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, diceAlreadyRolled_validDice) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.diceAlreadyRolled(camelOrange, 2);
    }
    catch(...) {
        FAIL() << "No exception expected";
    }
}

TEST(GameState, moveCamel_invalidDice_0) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.moveCamel(camelOrange, 0);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Invalid dice roll"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, moveCamel_invalidDice_4) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.moveCamel(camelOrange, 4);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Invalid dice roll"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, moveCamel_invalidCamel) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        gs.moveCamel(camelBlue, 2);
        FAIL() << "Expected std::logic_error";
    }
    catch (logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("Camel was not on the board"));
    }
    catch(...) {
        FAIL() << "Expected std::logic_error";
    }
}

TEST(GameState, moveCamel_validCamel) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.printMinimal();
    try{
        player_t player = gs.moveCamel(camelOrange, 2);
        EXPECT_EQ(player, UNKNOWN_PLAYER);
    }
    catch(...) {
        FAIL() << "No exception expected";
    }
}

// Test to show that when there are no options recalculate will simply report the results from the current camel.
TEST(GameState, moveCamel_BoardLive1Camel_move) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.moveCamel(camelOrange, 3);
    gs.print();
    gs.makeBoardLive();
    gs.printStats();
}

// Test to show that when there are no options recalculate will calculate the valid moves for this camel
TEST(GameState, moveCamel_BoardLive1Camel_nomove) {
    gameState gs;
    gs.addCamel(1, camelOrange);
    gs.print();
    gs.makeBoardLive();
    gs.printStats();
}

TEST(GameState, moveCamel_BoardLive2Camel_no_overlap) {
    gameState gs;
    gs.addCamel(0, camelOrange);
    gs.moveCamel(camelOrange, 1);
    gs.addCamel(2, camelBlue);
    gs.makeBoardLive();
    gs.printStats();
    EXPECT_EQ(gs.getNumResults(),3);
    EXPECT_EQ(gs.getCamelPFirst(camelOrange), 0);
    EXPECT_EQ(gs.getCamelPSecond(camelOrange), 100);
    EXPECT_EQ(gs.getCamelPLast(camelOrange), 100);
    
    EXPECT_EQ(gs.getCamelPFirst(camelBlue), 100);
    EXPECT_EQ(gs.getCamelPSecond(camelBlue), 0);
    EXPECT_EQ(gs.getCamelPLast(camelBlue), 0);
}

TEST(GameState, moveCamel_BoardLive2Camel_BlueOnTop) {
    gameState gs;
    gs.addCamel(0, camelOrange);
    gs.moveCamel(camelOrange, 2);
    gs.addCamel(2, camelBlue);
    gs.makeBoardLive();
    gs.printStats();
    
    EXPECT_EQ(gs.getNumResults(),3);
    EXPECT_EQ(gs.getCamelPFirst(camelOrange), 0);
    EXPECT_EQ(gs.getCamelPSecond(camelOrange), 100);
    EXPECT_EQ(gs.getCamelPLast(camelOrange), 100);
    
    EXPECT_EQ(gs.getCamelPFirst(camelBlue), 100);
    EXPECT_EQ(gs.getCamelPSecond(camelBlue), 0);
    EXPECT_EQ(gs.getCamelPLast(camelBlue), 0);
}

TEST(GameState, moveCamel_BoardLive2Camel_OrangeOnTop) {
    gameState gs;
    gs.addCamel(0, camelOrange);
    gs.moveCamel(camelOrange, 2);
    gs.addCamel(2, camelBlue);
    gs.makeBoardLive();
    gs.printStats();
}

TEST(GameState, moveCamel_BoardLive2Camel_overlap) {
    gameState gs;
    gs.addCamel(0, camelOrange);
    gs.addCamel(2, camelBlue);
    gs.makeBoardLive();
    gs.printStats();
    EXPECT_EQ(gs.getNumResults(),18);
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

