//
//  impediment.hpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#ifndef impediment_hpp
#define impediment_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

#include "enum_def.h"
#include "enum_impedimentType.h"


#define UNKNOWN_PLAYER 0xFF
typedef uint8_t player_t; /*! Identifies the player who placed impediments */

class Impediment {
    
private:

    impedimentType_e    m_impediment_type;        // Oasis or Swamp?
    player_t			m_impediment_owner;       // only valid if isPresent == true;

public:
    Impediment();
    
    //Impediment(Impediment&);
    impedimentType_e getImpedimentType();
    player_t   getImpedimentOwner();
    void addImpediment(impedimentType_e type, player_t owner);
    void removeImpediment();
    void print();
};
#endif /* impediment_hpp */
