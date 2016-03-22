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
#include <vector>
#include "impediment.hpp"

class Square
{
    uint8_t             m_location;
    bool                m_impedimentPresent; // Is there an impediment present on this square?
    Impediment          m_impediment;        // What type of impediment is present here?
    std::vector<camelColour_e> m_camelVec;  // Ordered list of players on the square.
                                             // front/begin is bottom of the pile

public:
    Square();                   // default constructor
    Square(Square&);             // copy constructor
    Square(uint8_t location);   // populate location with a default value.
    
    bool                isImpedimentPresent();	// Confirms if an impediment is present on this square.
    void				setLocation(uint8_t);   // Sets the location for this square
    uint8_t				getLocation();			// Returns the location.
    impedimentType_e    getImpedimentType();	//
    player_t            getImpedimentOwner();
    void				addImpediment(impedimentType_e type, player_t owner);
    void				removeImpediment();
    int8_t				getLocationToAdd();
    
    uint8_t				getNumCamels();   // Returns number of players on this square
    // Methods for initial setup
    void                addCamelToTop(camelColour_e);
    void                addCamelToBottom(camelColour_e);
    
    // Methods for moving stacks of players around.
    void                insertCamelsAtTop(std::vector<camelColour_e> vec_to_insert);
    void                insertCamelsAtBottom(std::vector<camelColour_e> vec_to_insert);

	camelColour_e		getCamelInFront();
	camelColour_e		getCamelInSecond();
	
    // will need to return list of entries from end of list
	void				print();
};

#endif /* square_hpp */
