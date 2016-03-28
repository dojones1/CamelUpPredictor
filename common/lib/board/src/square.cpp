//
//  square.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "square.hpp"
#include <iomanip>
#include "enum_conv.h"
#include "enum_camelColour.h"
using namespace std;

Square::Square():
    m_location(0),
    m_impediment_present(false)
{
}

Square::Square(uint8_t location):
	m_location(location),
	m_impediment_present(false)
{
}


bool Square::isImpedimentPresent() {
    return m_impediment_present;
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
	m_impediment_present = true;
}

void Square::removeImpediment()
{
	m_impediment.removeImpediment();
	m_impediment_present = false;
}

int8_t Square::getLocationToAdd()
{
	if (m_impediment_present == false)
	{
		// If no impediment is present then we can allow the player here
		return m_location;
	}
	else
	{
		// Now test the impedimentType.
		if (m_impediment.getImpedimentType() == imp_oasis)
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
	return m_camel_vec.size();
}

void Square::addCamelToTop(camelColour_e colour)
{
    m_camel_vec.push_back(colour);
}

void Square::addCamelToBottom(camelColour_e colour)
{
    m_camel_vec.insert(m_camel_vec.begin(),colour);
}

void Square::insertCamelsAtTop(vector<camelColour_e>::iterator begin, vector<camelColour_e>::iterator end)
{
	m_camel_vec.insert(m_camel_vec.end(), begin, end);
}

void Square::insertCamelsAtBottom(vector<camelColour_e>::iterator begin, vector<camelColour_e>::iterator end)
{
	m_camel_vec.insert(m_camel_vec.begin(), begin, end);
}

camelColour_e Square::getCamelInFront()
{
	if (m_camel_vec.size() > 0)
	{
		return m_camel_vec.at(m_camel_vec.size()-1);
	} 
	else return unknownCamel;
}

camelColour_e Square::getCamelInSecond()
{
	if (m_camel_vec.size() > 1)
	{
		return m_camel_vec.at(m_camel_vec.size()-2);
	} 
	else return unknownCamel;
}

camelColour_e Square::getCamelAtBottom()
{
    if (m_camel_vec.size() > 0)
    {
        return m_camel_vec.at(0);
    }
    else return unknownCamel;
}

void Square::print()
{
    cout.precision(2);
    cout << "[" << setw(2) <<  (m_location * 1) << "] ";
	if (m_impediment_present)
		m_impediment.print();
    if (m_camel_vec.size())
    {
        cout << "Camels[ " << m_camel_vec.size() << " ]: ";
            copy(m_camel_vec.cbegin(), m_camel_vec.cend(), ostream_iterator<camelColour_e>(cout," "));
    }
    
    cout << endl;
}