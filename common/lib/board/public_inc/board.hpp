//
//  board.h
//  camelUpPredictor
//
//  Created by Donald Jones on 22/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#ifndef board_h
#define board_h

#include <vector>
#include <map>
#include "square.hpp"
using namespace std;

#define NUM_SQUARES_ON_BOARD 18
#define NUM_VALID_SQUARES_ON_BOARD 16

class Board
{
    vector<Square>  m_square_vec; // Representation of the board.
    map<camelColour_e, uint8_t>    m_camelSquare_map; // Lookup table to map camel to its current square.

private:
    
public:
    Board();
    //Board(Board&);
    
    void addImpediment(uint8_t square, impedimentType_e type, player_t owner);
    void removeImpediment(uint8_t square);
    void addCamel(uint8_t square, camelColour_e camel);
    bool moveCamel(camelColour_e camel, uint8_t dice_roll); // returns false if a camel has moved over the finish line
    camelColour_e whichCamelIsLeading();
    camelColour_e whichCamelIsSecond();
};


#endif /* board_h */
