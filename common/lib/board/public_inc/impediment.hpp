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
#include "colour.h"
using namespace std;

typedef enum impedimentType_e
{
    invalidType,
    oasis,
    swamp
} impedimentType_e;

class Impediment {
    
private:

    impedimentType_e    m_impedimentType;        // Oasis or Swamp?
    player_t			      m_impedimentOwner;       // only valid if isPresent == true;

public:
    Impediment():
        m_impedimentType(invalidType),
        m_impedimentOwner(UNKNOWN_PLAYER)
    {}
    
    //Impediment(Impediment&);
    impedimentType_e getImpedimentType();
    player_t   getImpedimentOwner();
    void addImpediment(impedimentType_e type, player_t owner);
    void removeImpediment();
    void print(string parent);
};
#endif /* impediment_hpp */
