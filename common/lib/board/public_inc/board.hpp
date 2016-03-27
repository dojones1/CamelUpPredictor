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

    map<camelColour_e, uint8_t>    m_camelSquare_map; //! Lookup table to map camel to its current square.
public:
    vector<Square>  m_square_vec; //! Representation of the board.
    
public:
    //! Board Constructor.
    /*! Will initialise board with no contents, but with squares and their locations populated
     */
    Board();
    //Board(Board&);
    
    //! Adds an impediment to a square on the board
    /*!
        \param square the square to have the impediment added: 0-15
        \param type the type of impediment - oasis or swamp
        \param owner identifies the owner ID who placed the impediment
     */
    void addImpediment(uint8_t square, impedimentType_e type, player_t owner);
    
    //! Removes the impediment from a particular square
    void removeImpediment(uint8_t square);
    
    //! Removes all impediment from the entire board
    void removeAllImpediments();
    
    //! Counts the number of impediments present on the board
    /*!
        \return number of Impediments found
     */
    uint8_t countImpediments();
    
    //! Adds a camel on a particular square. By default it will be added to the top - as this should only be used upon initialisation
    void addCamel(uint8_t square, camelColour_e camel);
    
    //! Moves the camel and any passenger camels based upon the value of the dice roll. This will also take into account any impediment actions
    player_t moveCamel(camelColour_e camel, uint8_t dice_roll);
    
    //! Indicates whether a camel has crossed the finish line
    /*!
        \return true if at least one camel has crossed the finish line
     */
    bool hasCamelFinished();
    
    //! Identifies the camel which is leading the race
    camelColour_e whichCamelIsLeading();
    
    //! Identifies the camel which is coming second in the race
    camelColour_e whichCamelIsSecond();
    
    //! Identifies the camel which is losing the race
    camelColour_e whichCamelIsLast();
    
    // will need to return list of entries from end of list
    void				print();
    void				printMinimal();
};


#endif /* board_h */
