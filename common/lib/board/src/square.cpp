//
//  square.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "square.hpp"
using namespace std;

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

player_t   Square::getImpedimentOwner() {
    return m_impediment.getImpedimentOwner();
}

void Square::addImpediment(impedimentType_e type, player_t owner)
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

uint8_t Square::getNumCamels()
{
	return m_camelVec.size();
}

void Square::addCamelToTop(camelColour_e colour)
{
    m_camelVec.push_back(colour);
}

void Square::addCamelToBottom(camelColour_e colour)
{
    m_camelVec.insert(m_camelVec.begin(),colour);
}

void Square::insertCamelsAtTop(std::vector<camelColour_e> vec_to_insert)
{
	m_camelVec.insert(m_camelVec.end(), vec_to_insert.begin(), vec_to_insert.end());
}

void Square::insertCamelsAtBottom(std::vector<camelColour_e> vec_to_insert) 
{
	m_camelVec.insert(m_camelVec.begin(), vec_to_insert.begin(), vec_to_insert.end());
}

camelColour_e Square::getCamelInFront()
{
	if (m_camelVec.size() > 0)
	{
		return m_camelVec.at(m_camelVec.size()-1);
	} 
	else return unknownCamel;
}

camelColour_e Square::getCamelInSecond()
{
	if (m_camelVec.size() > 1)
	{
		return m_camelVec.at(m_camelVec.size()-2);
	} 
	else return unknownCamel;
}

void Square::print()
{
	cout << "m_impedimentPresent: " << m_impedimentPresent << endl;
	if (m_impedimentPresent)
		m_impediment.print("Square");
	cout << "m_camelVec: " << m_camelVec.size() << " camels" << endl;
	if (m_camelVec.size())
	{
		copy(m_camelVec.cbegin(), m_camelVec.cend(), ostream_iterator<camelColour_e>(cout," "));
		cout << endl;
	}
}