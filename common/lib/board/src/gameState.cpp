//
//  gameState.cpp
//  camelUpPredictor
//
//  Created by Donald Jones on 29/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include <exception>
#include <iomanip>
#include "gameState.hpp"


gameState::gameState():
    m_num_results(0),
    m_camels_still_to_roll(0),
    m_board_live(false)
{
    for (auto camel = 0; camel < COUNT_camelColour_e; camel++)
    {
        m_camel_info[camel].m_colour = static_cast<camelColour_e>(camel);
        m_camel_info[camel].m_on_board = false;
        m_camel_info[camel].m_dice_roll = 0;
        m_camel_info[camel].m_first_count = 0;
        m_camel_info[camel].m_second_count = 0;
        m_camel_info[camel].m_last_count = 0;
    }
}

void gameState::clearStats()
{
    for (auto camel = 0; camel < COUNT_camelColour_e; camel++)
    {
        m_camel_info[camel].m_first_count = 0;
        m_camel_info[camel].m_second_count = 0;
        m_camel_info[camel].m_last_count = 0;
    }
    m_num_results = 0;
}
void gameState::addImpediment(uint8_t square, impedimentType_e type, player_t owner)
{
    m_board.addImpediment(square, type, owner);
    if (m_board_live)
        recalculateStats();
}; // to be used during initialisation

void gameState::removeAllImpediments()
{
    m_board.removeAllImpediments();
}

void gameState::addCamel(uint8_t square, camelColour_e camel)
{
    m_board.addCamel(square, camel);
    m_camel_info[camel].m_colour = camel;
    m_camel_info[camel].m_dice_roll = 0;
    m_camel_info[camel].m_on_board = true;
    m_camels_still_to_roll++;
    
    // If this was the last camel to be added, then we can now calculate the stats from this state.
    if (m_camels_still_to_roll == 5)
    {
        m_board_live = true;
        recalculateStats();
    }
}

void gameState::validate_dice_roll(uint8_t dice_roll)
{
    if (dice_roll == 0 || dice_roll > 3)
        throw logic_error("Invalid dice roll");
}

void gameState::diceAlreadyRolled(camelColour_e camel, uint8_t dice_roll)
{
    validate_dice_roll(dice_roll);
    
    // Is the camel already on the board?
    if (m_camel_info[camel].m_on_board == false)
        throw logic_error("Camel was not on the board");
    
    m_camel_info[camel].m_dice_roll = dice_roll;
    
    if (m_camels_still_to_roll == 0)
        throw logic_error("m_camels_still_to_roll was already zero");
    m_camels_still_to_roll--;
    
    // no need to change the board state here.
}

player_t gameState::moveCamel(camelColour_e camel, uint8_t dice_roll)
{
    //cout << (m_camels_still_to_roll+1-1) <<" *** Move Camel[" << camel << "] " << (dice_roll+1-1) << endl;
    validate_dice_roll(dice_roll);
    
    // Is the camel already on the board?
    if (! m_camel_info[camel].m_on_board)
        throw logic_error("Camel was not on the board");

    if (m_camels_still_to_roll == 0)
        throw logic_error("m_camels_still_to_roll was already zero");

    m_camel_info[camel].m_dice_roll = dice_roll;
    
    m_camels_still_to_roll--;
    
    player_t imp_owner = m_board.moveCamel(camel, dice_roll);
    
    if (m_board_live)
        recalculateStats();
    return imp_owner;
}

void gameState::makeBoardLive()
{
    cout << "*** Board now Live *** " << endl;
    m_board_live = true;
    recalculateStats();
}

void gameState::addResult(camelColour_e first_camel, camelColour_e second_camel, camelColour_e last_camel)
{
    m_camel_info[first_camel].m_first_count++;
    m_camel_info[second_camel].m_second_count++;
    m_camel_info[last_camel].m_last_count++;
    m_num_results++;
}

void gameState::recalculateStats()
{
    //cout << (m_camels_still_to_roll+1-1) << " *** Recalculating Stats ***" << endl;
    // Now need to regenerate all of our stats.
    // Clear our own stats
    clearStats();
    
    // Loop over the camels still to move
    bool camel_found = false; // have we found a camel to move?
    for (auto & camel_info: m_camel_info)
    {
        //cout << "Testing Camel:" << camel_info.m_colour<< " " << (camel_info.m_on_board == true) << " "<< (camel_info.m_dice_roll+1 -1) << endl;
        // Is it on the board and is it still to roll
        if (camel_info.m_on_board &&
            camel_info.m_dice_roll == 0)
        {
            camel_found = true;
            // Loop over the dice_rolls
            for (auto dice_roll = 1; dice_roll < 4; dice_roll++)
            {
                //cout << (m_camels_still_to_roll+1-1) << " Rolling for Camel:" << camel_info.m_colour<< " " << " "<< (dice_roll+1 -1) << endl;
                // Create a new game State based upon this.
                gameState gsNext;
                gsNext = *this;
                
                // Update its state with the move
                gsNext.moveCamel(camel_info.m_colour, dice_roll);
                
                // Get it to recalculate the stats for any substates
                gsNext.recalculateStats();

                uint16_t num_results = gsNext.getNumResults();
                m_num_results += num_results;
                //cout << "Incremented num_results by " << num_results << " to " << m_num_results << endl;
                
                // Add the stats from the completed calculation into the parent entry.
                for (auto statCamel = 1; statCamel < COUNT_camelColour_e; statCamel++)
                {
                    uint16_t first_count = 0;
                    uint16_t second_count = 0;
                    uint16_t last_count = 0;
                    gsNext.getStats(static_cast<camelColour_e>(statCamel), first_count, second_count, last_count);
                    
                    m_camel_info[statCamel].m_first_count  += first_count;
                    m_camel_info[statCamel].m_second_count += second_count;
                    m_camel_info[statCamel].m_last_count += last_count;
                    
                    if (0)
                    // if (first_count || second_count || last_count)
                    {
                        cout << "Incrementing states for: ";
                        cout << setw(10) << static_cast<camelColour_e>(statCamel) << ": ";
                        cout << setw(8) << first_count << " ";
                        cout << setw(8) << second_count << " ";
                        cout << setw(8) << last_count << " ";
                        cout << endl;
                    }
                }
            }
        }
    }
    
    // Did a camel move?
    if (!camel_found)
    {
        // No: Then we are in a terminal state. record our current state to the metrics.
        //cout << "At leaf node" << endl;
        addResult(m_board.whichCamelIsLeading(),m_board.whichCamelIsSecond(),m_board.whichCamelIsLast());
    }
}

void gameState::getStats(camelColour_e camel, uint16_t &first_count, uint16_t &second_count, uint16_t &last_count)
{
    first_count  = m_camel_info[camel].m_first_count;
    second_count = m_camel_info[camel].m_second_count;
    last_count   = m_camel_info[camel].m_last_count;
}

uint16_t gameState::getNumResults()
{
    return m_num_results;
}

float gameState::getCamelPFirst(camelColour_e camel)
{
    return (m_camel_info[camel].m_first_count * 100) / m_num_results;
}

float gameState::getCamelPSecond(camelColour_e camel)
{
    return (m_camel_info[camel].m_second_count * 100) / m_num_results;
   
}

float gameState::getCamelPLast(camelColour_e camel)
{
    return (m_camel_info[camel].m_last_count * 100) / m_num_results;
    
}

void gameState::print()
{
    cout.setf(ios::boolalpha);
    cout << "GameState: " << m_board_live << m_camels_still_to_roll << endl;
    m_board.print();
    cout << endl;
    // Now show camel state
    for (auto const & camel: m_camel_info)
    {
        cout << camel.m_colour << " ";
        cout << camel.m_on_board << " ";
        cout << camel.m_dice_roll << " ";
        cout << camel.m_first_count << " ";
        cout << camel.m_second_count << " ";
        cout << camel.m_last_count;
        cout << endl;
    }
}

void gameState::printMinimal()
{
    cout << "GameState: " << m_board_live << m_camels_still_to_roll << endl;
    m_board.printMinimal();
    
    // Now show camel state
    for (auto const & camel: m_camel_info)
    {
        // Only print info on camels on board
        if (camel.m_on_board)
        {
            cout << camel.m_colour << " ";
            cout << camel.m_dice_roll << " ";
            cout << camel.m_first_count << " ";
            cout << camel.m_second_count << " ";
            cout << camel.m_last_count;
            cout << endl;
        }
    }
}

void gameState::printStats()
{
    cout << "Stats: " << m_num_results << " States" << endl;
    cout << "Colour            p(1st)     p(2nd) p(last)" << endl;
    // Now show camel state
    for (auto const & camel: m_camel_info)
    {
        // Only print info on camels on board
        if (camel.m_on_board && m_num_results)
        {
            cout << setw(10) << camel.m_colour << ": ";
            cout << setw(8) << (camel.m_first_count * 100) / m_num_results << "%";
            cout << setw(8) << (camel.m_second_count * 100) / m_num_results << "%";
            cout << setw(8) << (camel.m_last_count * 100) / m_num_results << "%";
            cout << endl;
        }
    }
}