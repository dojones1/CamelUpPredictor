//
//  square.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "square.hpp"

Square::Square():
    m_location(0),
    m_impedimentPresent(false)
{
}

Square::Square(uint8_t location):
	m_location(location),
	m_impedimentPresent(false)
{
}

bool Square::isImpedimentPresent() {
    return m_impedimentPresent;
}

impedimentType_e    Square::getImpedimentType()
{
    return m_impediment.getImpedimentType();
}

void Square::setLocation(uint8_t location)
{
	m_location = location;
}

uint8_t   Square::getLocation()
{
    return m_location;
}

playerColour_e   Square::getImpedimentOwner() {
    return m_impediment.getImpedimentOwner();
}

void Square::addImpediment(impedimentType_e type, playerColour_e owner)
{
	m_impediment.addImpediment(type, owner);
	m_impedimentPresent = true;
}

void Square::removeImpediment()
{
	m_impediment.removeImpediment();
	m_impedimentPresent = false;
}

int8_t Square::getLocationToAdd()
{
	if (m_impedimentPresent == false)
	{
		// If no impediment is present then we can allow the player here
		return m_location;
	}
	else
	{
		// Now test the impedimentType.
		if (m_impediment.getImpedimentType() == oasis)
		{
			// Oasis means that the player can be moved forward
			return m_location + 1;
		}
		else
		{
			// Swamp means that the player will be pushed back
			// Need to make sure that we are not on the first square.
			if (m_location > 0)
			{
				return m_location - 1;
			}
			else
			{
				// Can't go negative
				return m_location;
			}
		}
	}
}

void Square::addPlayerToTop(playerColour_e colour)
{
    m_playerList.push_front(colour);
}

void Square::addPlayerToBottom(playerColour_e colour)
{
    m_playerList.push_back(colour);
}