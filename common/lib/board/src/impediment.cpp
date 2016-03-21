//
//  impediment.cpp
//  testview
//
//  Created by Donald Jones on 20/03/2016.
//  Copyright © 2016 Donald Jones. All rights reserved.
//

#include "impediment.hpp"
impedimentType_e Impediment::getImpedimentType()
{
    return m_impedimentType;
}

playerColour_e Impediment::getImpedimentOwner()
{
    return m_impedimentOwner;
}

void Impediment::addImpediment(impedimentType_e type, playerColour_e owner)
{
    m_impedimentType  = type;
    m_impedimentOwner = owner;
}

void Impediment::removeImpediment()
{
    m_impedimentType  = invalidType;
    m_impedimentOwner = unknownPlayer;
}