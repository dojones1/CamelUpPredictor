//
//  impediment.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "impediment.hpp"
#include "enum_conv.h"
#include "enum_impedimentType.h"

Impediment::Impediment():
m_impediment_type(imp_invalidType),
m_impediment_owner(UNKNOWN_PLAYER)
{}

impedimentType_e Impediment::getImpedimentType()
{
    return m_impediment_type;
}

player_t Impediment::getImpedimentOwner()
{
    return m_impediment_owner;
}

void Impediment::addImpediment(impedimentType_e type, player_t owner)
{
    m_impediment_type  = type;
    m_impediment_owner = owner;
}

void Impediment::removeImpediment()
{
    m_impediment_type  = imp_invalidType;
    m_impediment_owner = UNKNOWN_PLAYER;
}

void Impediment::print()
{
    cout << "Impediment: " << m_impediment_type << " => " << (m_impediment_owner*1);
}