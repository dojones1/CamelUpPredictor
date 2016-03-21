//
//  square.hpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#ifndef square_hpp
#define square_hpp

#include <stdio.h>
#include <list>
#include "impediment.hpp"

class Square
{
    uint8_t             m_location;
    bool                m_impedimentPresent; // Is there an impediment present on this square?
    Impediment          m_impediment;        // What type of impediment is present here?
    std::list<playerColour_e> m_playerList;  // Ordered list of players on the square.
                                             // front is top of the pile

public:
    Square();                   // default constructor
    Square(uint8_t location);   // populate location with a default value.
    
    bool                isImpedimentPresent();
    void				setLocation(uint8_t);
    uint8_t				getLocation();
    impedimentType_e    getImpedimentType();
    playerColour_e      getImpedimentOwner();
    void				addImpediment(impedimentType_e type, playerColour_e owner);
    void				removeImpediment();
    int8_t				getLocationToAdd();
    
    // Methods for initial setup
    void                addPlayerToTop(playerColour_e);
    void                addPlayerToBottom(playerColour_e);
    
    // Methods for moving stacks of players around.
    //void                splicePlayersToTop( const_iterator position, list&& x,
    //                                        const_iterator first, const_iterator last);
    //void                splicePlayersToBottom(playerColour_e);

    // will need to return list of entries from end of list

};

#endif /* square_hpp */
