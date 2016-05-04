//
//  main.cpp
//  CLI for the CamelUpPredictor library
//
//  Created by Donald Jones on 13/04/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "gameState.hpp"
#include <map>
#include <utility>
using namespace std;


void toLower(basic_string<char>& s) {
    for (basic_string<char>::iterator p = s.begin();
         p != s.end(); ++p) {
        *p = tolower(*p);
    }
}

void toLower(basic_string<wchar_t>& s) {
    for (basic_string<wchar_t>::iterator p = s.begin();
         p != s.end(); ++p) {
        *p = towlower(*p);
    }
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}



void printPrompt()
{
    cout << "$: ";
}

void printHeader()
{
    cout << "*** Camel Up Predictor ***" << endl;
}

bool printHelp(gameState &)
{
    cout << "help" << endl;
    cout << "addImp" << endl;
 	cout << "rmAllImps" << endl;
    cout << "addCamel" << endl;
    cout << "live" << endl;
	cout << "moveCamel" << endl;
	cout << "state" << endl;
    cout << "stats" << endl;
    cout << "quit" << endl;
    return true;
}

typedef map<unsigned int, impedimentType_e> imp_map;
imp_map impMap;

impedimentType_e getImp()
{
    impedimentType_e imp = imp_invalidType;
    string imp_s;
    while (imp == imp_invalidType)
    {
        cout << "Please enter Impediment Type (oasis | swamp): ";
        cin >> imp_s;
        toLower(imp_s);
        
        // Is this a known command?
        if (impMap.find(str2int(imp_s.c_str())) == impMap.end())
        {
            cout << "Unknown imp: " << imp_s << endl;
        }
        else
        {
            
            try {
                imp = impMap[str2int(imp_s.c_str())];
            }
            catch (const std::exception& e) {
                cout << "Invalid Impediment" << endl;
            }
        }
    }
    
    return imp;
}


typedef map<unsigned int, camelColour_e> camel_map;
camel_map camelMap;

camelColour_e getCamel()
{
    camelColour_e camel = unknownCamel;
    string camel_s;
    while (camel == unknownCamel)
    {
        cout << "Please enter Camel: ";
        cin >> camel_s;
        toLower(camel_s);
        
        // Is this a known command?
        if (camelMap.find(str2int(camel_s.c_str())) == camelMap.end())
        {
            cout << "Unknown Camel: " << camel_s << endl;
        }
        else
        {
            
            try {
                camel = camelMap[str2int(camel_s.c_str())];
            }
            catch (const std::exception& e) {
                cout << "Invalid camel" << endl;
            }
        }
    }
    
    return camel;
}

uint8_t getDiceRoll()
{
    int dice = 7;
    
    while (dice < 1 || dice > 6)
    {
        cout << "Please enter Dice Roll";
        cin >> dice;
        if (dice < 1 || dice > 6)
        {
            cout << "Invalid dice value: " << dice << endl;
        }
    }
    return static_cast<uint8_t>(dice);
}

uint8_t getSquare()
{
    int square = 17;
    while (square > 16 || square < 1)
    {
        cout << "Please enter Square: ";
        cin >> square;
        if (square >16 || square < 1)
        {
            cout << "Square invalid: " << square << endl;
        }

    }
    return static_cast<uint8_t>(square-1);
}

player_t getPlayer()
{
    int player = 9;
    while (player > 8 || player < 1)
    {
        cout << "Please enter Player: ";
        cin >> player;
        if (player >16 || player < 1)
        {
            cout << "Player invalid: " << player << endl;
        }
        
    }
    return static_cast<player_t>(player);
}

bool addImpediment(gameState &gs)
{
    uint8_t square = getSquare();
    impedimentType_e imp = getImp();
    player_t owner = getPlayer();
    
    gs.addImpediment(square, imp, owner);
    cout << "Added " << imp << " owned by " << (owner+1-1) << " at square " << (square+1) << endl;
    return true;
}
bool rmAllImps(gameState &gs)
{
    gs.removeAllImpediments();
	return true;
}

bool addCamel(gameState &gs)
{
    uint8_t square = getSquare();
    camelColour_e camel = getCamel();

    gs.addCamel(square, camel);
    cout << "Added " << camel << " at square " << (square+1) << endl;
	return true;
}

bool live(gameState &gs)
{
	gs.makeBoardLive();
    cout << "Board is now live" << endl;
	return true;
}

bool moveCamel(gameState& gs)
{
    camelColour_e camel = getCamel();
    uint8_t dice_roll = getDiceRoll();
    gs.moveCamel(camel, dice_roll); // to be used to update the state during processing.
    cout << "Moved " << camel << " " << (dice_roll+1-1) << "spaces" << endl;
	return true;
}

bool quit(gameState &)
{
    cout << "Leaving so soon?" << endl;
    return false;
}

bool state(gameState &gs)
{
	gs.print();
	return true;
}

bool stats(gameState &gs)
{
	gs.printStats();
	return true;
}

typedef bool (*ScriptFunction)(gameState &); // function pointer type
typedef map<unsigned int, ScriptFunction> script_map;

gameState gs;

int main (int , const char *[])
{
    script_map cmdMap;

    cmdMap[str2int("help")] = printHelp;
    cmdMap[str2int("quit")] = quit;
    cmdMap[str2int("addImp")] = addImpediment;
    cmdMap[str2int("rmAllImps")] = rmAllImps;
    cmdMap[str2int("addCamel")] = addCamel;
    cmdMap[str2int("moveCamel")] = moveCamel;
    cmdMap[str2int("live")] = live;
    cmdMap[str2int("stats")] = stats;
    cmdMap[str2int("state")] = state;
    
    camelMap[str2int("orange")] = camelOrange;
    camelMap[str2int("yellow")] = camelYellow;
    camelMap[str2int("green")]  = camelGreen;
    camelMap[str2int("blue")]   = camelBlue;
    camelMap[str2int("white")]  = camelWhite;
    camelMap[str2int("o")] = camelOrange;
    camelMap[str2int("y")] = camelYellow;
    camelMap[str2int("g")]  = camelGreen;
    camelMap[str2int("b")]   = camelBlue;
    camelMap[str2int("w")]  = camelWhite;
    
    impMap[str2int("oasis")] = imp_oasis;
    impMap[str2int("swamp")] = imp_swamp;
    impMap[str2int("o")] = imp_oasis;
    impMap[str2int("s")] = imp_swamp;
    
    printHeader();

	bool running = true;
	while (running)
	{
	    printPrompt();

	    string cmd;
	    cin >> cmd;
        
        // Is this a known command?
        if (cmdMap.find(str2int(cmd.c_str())) == cmdMap.end())
        {
            cout << "Unknown Command: " << cmd << endl;
        }
        else
        {
            
            try {
                running = cmdMap[str2int(cmd.c_str())](gs);
            }
            catch (const std::exception& e) {
                cout << "Invalid command" << endl;
                running = false;
            }
        }
    }
    return 0;
}