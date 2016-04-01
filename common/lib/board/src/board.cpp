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
    if (square < NUM_VALID_SQUARES_ON_BOARD)
    {
        if (((square+1) < NUM_VALID_SQUARES_ON_BOARD) &&
            m_square_vec.at(square+1).isImpedimentPresent())
        {
            throw logic_error("Cannot place an impediment when there is one on the next square");
        }
    
        if ((square > 0) &&
            m_square_vec.at(square-1).isImpedimentPresent())
        {
            throw logic_error("Cannot place an impediment when there is one on the previous square");
        }

        m_square_vec.at(square).addImpediment(type, owner);
    }
};

void Board::removeImpediment(uint8_t square)
{
    if (square < NUM_VALID_SQUARES_ON_BOARD)
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

player_t Board::moveCamel(camelColour_e camel, uint8_t dice_roll)
{
    uint8_t initSquare = m_camelSquare_map[camel];
    uint8_t initDestSquare = initSquare + dice_roll;
    uint8_t actDestSquare = m_square_vec.at(initDestSquare).getLocationToAdd();
    
    vector<camelColour_e> &srcVec = m_square_vec.at(initSquare).m_camel_vec;
    Square &dstVec = m_square_vec.at(actDestSquare);
    

    // Find list of camels to be moved
    auto it_start_of_list = srcVec.begin();
    
    // Find iterator for start of list
    for (auto it = srcVec.begin(); it != srcVec.end(); ++it)
    {
        // Is this the camel that we are looking for?
        if (*it == camel)
        {
            it_start_of_list = it;
            break;
        }
    }

    // Print the list to move:
/*
    cout << "List to move:";
    for (auto it = it_start_of_list; (it != srcVec.end()); ++it)
    {
        cout << ' ' << *it ;
    }
    cout << endl;
*/    
    vector<camelColour_e> tmpVec;
    tmpVec.insert(tmpVec.begin(), it_start_of_list, srcVec.end());
    
    // Now remove the camels from the original list
    srcVec.erase(it_start_of_list, srcVec.end());
    
    player_t impediment_owner = UNKNOWN_PLAYER;
    
    // Now need the complex logic to move a camel from one square to another.
    if (actDestSquare == initDestSquare)
    {
        // No impediment so just need to add it on top
        dstVec.insertCamelsAtTop(tmpVec.begin(), tmpVec.end());
    }
    else if (actDestSquare > initDestSquare)
    {
        // Travelled via oasis so this camel and passengers should be added on top.
        dstVec.insertCamelsAtTop(tmpVec.begin(), tmpVec.end());
        impediment_owner = m_square_vec.at(initDestSquare).getImpedimentOwner();
    }
    else
    {
        // Must have gone backwards from initial destination and so, must have gone via swamp.
        // Therefore must add the camel and passengers to the bottom of the destination.
        dstVec.insertCamelsAtBottom(tmpVec.begin(), tmpVec.end());
        impediment_owner = m_square_vec.at(initDestSquare).getImpedimentOwner();
    }
    
    // Need to update the location of all moved camels
    m_camelSquare_map[camel] = actDestSquare;
    
    return impediment_owner;
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
    for (auto idx = NUM_SQUARES_ON_BOARD-1; idx >= 0; idx--)
    {
        if (m_square_vec.at(idx).getNumCamels())
        {
            return m_square_vec.at(idx).getCamelInFront();
        }
    }
    return unknownCamel;
};

camelColour_e Board::whichCamelIsSecond()
{
    bool found_first = false;
    for (auto idx = NUM_SQUARES_ON_BOARD-1; idx >= 0; idx--)
    {
        if (!found_first)
        {
            if (m_square_vec.at(idx).getNumCamels() == 0)
            {
                // No camels here so do nothing
            }
            else if (m_square_vec.at(idx).getNumCamels() == 1)
            {
                // Only one camel here, so this must be the first
                found_first = true;
            }
            else {
                // More than one camel here so return the second one
                return m_square_vec.at(idx).getCamelInSecond();
            }
        }
        else if (m_square_vec.at(idx).getNumCamels())
        {
            // The second camel must be the camel in front on this square
            return m_square_vec.at(idx).getCamelInFront();
        }
    }
    return unknownCamel;
};

camelColour_e Board::whichCamelIsLast()
{
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        if (m_square_vec.at(idx).getNumCamels())
        {
            return m_square_vec.at(idx).getCamelAtBottom();
        }
    }
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

// will need to return list of entries from end of list
void Board::printMinimal()
{
    for (auto idx = 0; idx < NUM_SQUARES_ON_BOARD; idx++)
    {
        if (m_square_vec.at(idx).getNumCamels() ||
            m_square_vec.at(idx).isImpedimentPresent())
            m_square_vec.at(idx).print();
    }
}