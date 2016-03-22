//
//  board.cpp
//  camelUpPredictor
//
//  Created by Donald Jones on 22/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include <stdio.h>
#include "board.hpp"

Board::Board()
{
    //m_square_vec.reserve(NUM_SQUARES_ON_BOARD);
    uint8_t idx = 0;
    for (Square sq:m_square_vec)
    {
        sq.setLocation(idx++);
    }
}

void Board::addImpediment(uint8_t square, impedimentType_e type, player_t owner)
{
    m_square_vec.at(square).addImpediment(type, owner);
};

void Board::removeImpediment(uint8_t square)
{
    m_square_vec.at(square).removeImpediment();
};

void Board::addCamel(uint8_t square, camelColour_e camel)
{
    m_square_vec.at(square).addCamelToTop(camel);
    m_camelSquare_map[camel] = square;
};

bool Board::moveCamel(camelColour_e camel, uint8_t dice_roll)
{
    uint8_t initSquare = m_camelSquare_map[camel];
    uint8_t initDestSquare = initSquare + dice_roll;
    uint8_t actDestSquare = m_square_vec.at(initDestSquare).getLocationToAdd();
    
    // Now need the complex logic to move a camel from one square to another.
    return (actDestSquare >= NUM_VALID_SQUARES_ON_BOARD);
}; // returns false if a camel has moved over the finish line

camelColour_e Board::whichCamelIsLeading() { return unknownCamel;};

camelColour_e Board::whichCamelIsSecond()  { return unknownCamel;};