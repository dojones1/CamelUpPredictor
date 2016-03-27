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

    map<camelColour_e, uint8_t>    m_camelSquare_map; // Lookup table to map camel to its current square.
public:
    vector<Square>  m_square_vec; // Representation of the board.
    
public:
    Board();
    //Board(Board&);
    
    void addImpediment(uint8_t square, impedimentType_e type, player_t owner);
    void removeImpediment(uint8_t square);
    void removeAllImpediments();
    uint8_t countImpediments();
    void addCamel(uint8_t square, camelColour_e camel);
    void moveCamel(camelColour_e camel, uint8_t dice_roll);
    bool hasCamelFinished();
    camelColour_e whichCamelIsLeading();
    camelColour_e whichCamelIsSecond();
    
    // will need to return list of entries from end of list
    void				print();
};


#endif /* board_h */
