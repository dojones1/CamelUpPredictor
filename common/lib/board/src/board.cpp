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
    m_square_vec.reserve(NUM_SQUARES_ON_BOARD);
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        Square sq(idx);
        m_square_vec.push_back(sq);
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

void Board::removeAllImpediments()
{
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        if (m_square_vec.at(idx).isImpedimentPresent())
        {
            m_square_vec.at(idx).removeImpediment();
        }
    }
}

uint8_t Board::countImpediments()
{
    uint8_t count = 0;
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        if (m_square_vec.at(idx).isImpedimentPresent())
        {
            count++;
        }
    }
    return count;
}

void Board::addCamel(uint8_t square, camelColour_e camel)
{
    m_square_vec.at(square).addCamelToTop(camel);
    m_camelSquare_map[camel] = square;
};

void Board::moveCamel(camelColour_e camel, uint8_t dice_roll)
{
    uint8_t initSquare = m_camelSquare_map[camel];
    uint8_t initDestSquare = initSquare + dice_roll;
    uint8_t actDestSquare = m_square_vec.at(initDestSquare).getLocationToAdd();
    
    // Now need the complex logic to move a camel from one square to another.
    // @TODO
    actDestSquare = actDestSquare+1 -1;
}; // returns false if a camel has moved over the finish line

bool Board::hasCamelFinished()
{
    bool camelFinished = false;
    for (auto idx = NUM_VALID_SQUARES_ON_BOARD; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        if (m_square_vec.at(idx).getNumCamels())
        {
            camelFinished = true;
            return camelFinished;
        }
    }
    return camelFinished;
}

camelColour_e Board::whichCamelIsLeading()
{
    // @TODO
    return unknownCamel;
};

camelColour_e Board::whichCamelIsSecond()
{
    // @TODO
    return unknownCamel;
};

// will need to return list of entries from end of list
void Board::print()
{
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        m_square_vec.at(idx).print();
    }
}