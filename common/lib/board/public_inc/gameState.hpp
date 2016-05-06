//
//  gameState.hpp
//  camelUpPredictor
//
//  Created by Donald Jones on 29/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#ifndef gameState_hpp
#define gameState_hpp

#include <stdio.h>
#include "board.hpp"

class gameState {
    struct camelState_s{
        camelColour_e m_colour;
        bool m_on_board;         // Indicates if the camel has been placed on the board
        uint8_t m_dice_roll;    // what dice roll did it do? 0 = unrolled
        uint16_t m_first_count;
        uint16_t m_second_count;
        uint16_t m_last_count;
    };
    
    uint16_t m_num_results;
    Board m_board;
    camelState_s m_camel_info[COUNT_camelColour_e];
    uint8_t m_camels_still_to_roll;
    bool m_board_live; // Is the board now accurate for the current state of play?

private:
    void clearStats();
    void validate_dice_roll(uint8_t dice_roll);
    void addResult(camelColour_e first_camel, camelColour_e second_camel, camelColour_e last_camel);
    
public:
    gameState();
    void addImpediment(uint8_t square, impedimentType_e type, player_t owner); // to be used during initialisation
    void removeAllImpediments();
    void addCamel(uint8_t square, camelColour_e camel); // to be used to add a camel during board initialisation
    void makeBoardLive();  // to be used to force the game state to live even if insufficient camels have been added
    void diceAlreadyRolled(camelColour_e camel, uint8_t dice_roll); // to be used if the dice has already been rolled to reach an initial state.
    player_t moveCamel(camelColour_e camel, uint8_t dice_roll); // to be used to update the state during processing.
    bool hasCamelFinished();
    void recalculateStats();
    void getStats(camelColour_e camel, uint16_t &first_count, uint16_t &second_count, uint16_t &last_count);
    uint16_t getNumResults();
    float getCamelPFirst(camelColour_e camel);
    float getCamelPSecond(camelColour_e camel);
    float getCamelPLast(camelColour_e camel);
    
    camelColour_e getMostLikelyFirst();
    camelColour_e getMostLikelySecond();
    camelColour_e getMostLikelyLast();
    
    void print();
    void printMinimal();
    void printStats();
};

#endif /* gameState_hpp */
