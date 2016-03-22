// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "square.hpp"
#include "gtest/gtest.h"
using namespace std;

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

/*
    Square(uint8_t location);   // populate location with a default value.
    bool                isImpedimentPresent();
    uint8_t				getLocation;
    impedimentType_e    getImpedimentType();
    playerColour_e      getImpedimentOwner();
    void				addImpediment(impedimentType_e type, playerColour_e owner);
    void				removeImpediment();
    int8_t				getLocationToAdd();
    
    // Methods for initial setup
    void                addCamelToTop(playerColour_e);
    void                addCamelToBottom(playerColour_e);
*/

TEST(Square_init1, Positive) {
	Square sq(1);
    
    EXPECT_EQ(sq.getLocation(),	1);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
}

TEST(Square_init2, Positive) {
	Square sq;
    sq.setLocation(2);
    EXPECT_EQ(sq.getLocation(),	2);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
}

TEST(Square_addRemoveImpediment, Positive) {
	Square sq(1);
	EXPECT_EQ(sq.getLocation(),	1);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
    
    sq.addImpediment(oasis, 4);
    EXPECT_EQ(sq.getImpedimentType(),	oasis);
    EXPECT_EQ(sq.getImpedimentOwner(),  4);
    EXPECT_EQ(sq.isImpedimentPresent(), true);

	sq.removeImpediment();
    EXPECT_EQ(sq.getImpedimentType(),	invalidType);
    EXPECT_EQ(sq.getImpedimentOwner(),  UNKNOWN_PLAYER);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
}

TEST(Square_LocationToAdd_Oasis, Positive)
{
	Square sq(0);
	EXPECT_EQ(sq.getLocation(),	0);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
    
    sq.addImpediment(oasis, 3);
    EXPECT_EQ(sq.getImpedimentType(),	oasis);
    EXPECT_EQ(sq.getImpedimentOwner(),  3);
    EXPECT_EQ(sq.isImpedimentPresent(), true);
    EXPECT_EQ(sq.getLocationToAdd(), 1);
}

TEST(Square_LocationToAdd_Swamp, Positive)
{
	Square sq(1);
	EXPECT_EQ(sq.getLocation(),	1);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
    
    sq.addImpediment(swamp, 2);
    //sq.print();
    EXPECT_EQ(sq.getImpedimentType(),	swamp);
    EXPECT_EQ(sq.getImpedimentOwner(),  2);
    EXPECT_EQ(sq.isImpedimentPresent(), true);
    EXPECT_EQ(sq.getLocationToAdd(), 0);
}

TEST(Square_LocationToAdd_Swamp_0, Positive)
{
	Square sq(0);
	EXPECT_EQ(sq.getLocation(),	0);
    EXPECT_EQ(sq.isImpedimentPresent(), false);
    
    sq.addImpediment(swamp, 4);
    EXPECT_EQ(sq.getImpedimentType(),	swamp);
    EXPECT_EQ(sq.getImpedimentOwner(),  4);
    EXPECT_EQ(sq.isImpedimentPresent(), true);
    EXPECT_EQ(sq.getLocationToAdd(), 0);
}

TEST(Square_vec_insert_at_top_empty_vec, Positive)
{
	Square sq(0);
	vector<camelColour_e> vec_to_insert;
	
	EXPECT_EQ(sq.getNumCamels(), 0);
	vec_to_insert.push_back(camelBlue);
	vec_to_insert.push_back(camelGreen);
	
	sq.insertCamelsAtTop(vec_to_insert);
	EXPECT_EQ(sq.getNumCamels(), 2);
}

TEST(Square_vec_insert_at_bottom_empty_list, Positive)
{
	Square sq(0);
	vector<camelColour_e> vec_to_insert;
	
	EXPECT_EQ(sq.getNumCamels(), 0);
	
	// Build the list to insert
	vec_to_insert.push_back(camelBlue);
	vec_to_insert.push_back(camelGreen);
	
	sq.insertCamelsAtBottom(vec_to_insert);
	EXPECT_EQ(sq.getNumCamels(), 2);
	EXPECT_EQ(sq.getCamelInFront(), camelGreen);
	EXPECT_EQ(sq.getCamelInSecond(), camelBlue);
}

TEST(Square_vec_insert_at_Top_existing_vec, Positive)
{
	Square sq(0);
	sq.addCamelToTop(camelBlue);
	EXPECT_EQ(sq.getNumCamels(), 1);
	EXPECT_EQ(sq.getCamelInFront(), camelBlue);
	
	sq.addCamelToTop(camelOrange);
	EXPECT_EQ(sq.getNumCamels(), 2);
	EXPECT_EQ(sq.getCamelInFront(), camelOrange);
	EXPECT_EQ(sq.getCamelInSecond(), camelBlue);
}

TEST(Square_vec_value_at, Positive)
{
	Square sq(0);
	sq.addCamelToTop(camelOrange);
	sq.addCamelToTop(camelYellow);
	sq.addCamelToTop(camelGreen);
	
	EXPECT_EQ(sq.getCamelInFront(), camelGreen);
	EXPECT_EQ(sq.getCamelInSecond(), camelYellow);
}

TEST(Square_getCamelIn_1_value, Negative)
{
	Square sq(0);
	sq.addCamelToTop(camelOrange);
	
	EXPECT_EQ(sq.getCamelInFront(), camelOrange);
	EXPECT_EQ(sq.getCamelInSecond(), unknownCamel);
}

TEST(Square_getCamelIn_0_value, Negative)
{
	Square sq(0);
	EXPECT_EQ(sq.getCamelInFront(), unknownCamel);
	EXPECT_EQ(sq.getCamelInSecond(), unknownCamel);
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
