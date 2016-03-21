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

#include "colour.h"

typedef enum impedimentType_e
{
    invalidType,
    oasis,
    swamp
} impedimentType_e;

class Impediment {
    
private:

    impedimentType_e    m_impedimentType;        // Oasis or Swamp?
    playerColour_e      m_impedimentOwner;       // only valid if isPresent == true;

public:
    Impediment():
        m_impedimentType(invalidType),
        m_impedimentOwner(unknownPlayer)
    {}
    impedimentType_e getImpedimentType();
    playerColour_e   getImpedimentOwner();
    void addImpediment(impedimentType_e type, playerColour_e owner);
    void removeImpediment();
};
#endif /* impediment_hpp */
