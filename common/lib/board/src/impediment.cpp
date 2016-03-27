//
//  impediment.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "impediment.hpp"

Impediment::Impediment():
m_impedimentType(invalidType),
m_impedimentOwner(UNKNOWN_PLAYER)
{}

impedimentType_e Impediment::getImpedimentType()
{
    return m_impedimentType;
}

player_t Impediment::getImpedimentOwner()
{
    return m_impedimentOwner;
}

void Impediment::addImpediment(impedimentType_e type, player_t owner)
{
    m_impedimentType  = type;
    m_impedimentOwner = owner;
}

void Impediment::removeImpediment()
{
    m_impedimentType  = invalidType;
    m_impedimentOwner = UNKNOWN_PLAYER;
}

void Impediment::print()
{
    cout << "Impediment: " << m_impedimentType << " => " << (m_impedimentOwner*1);
}