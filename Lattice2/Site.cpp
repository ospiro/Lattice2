//
//  Site.cpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#include "Site.hpp"
Site::Site()
{
    species = 0;
}
void Site::die()
{
    species = 0;
}
void Site::grow(int newSpecies)
{
    species = newSpecies;
}
bool Site::isEmpty()
{
    return (species==0);
}
void Site::fillNeighborArray(unsigned long numNeighbors, vector<Site*> newNeighbors)
{
    for(int i  = 0; i<numNeighbors;i++)
    {
        neighbors.push_back(newNeighbors[i]);
    }
}

bool Site::isDeveloped()
{
    return (species==4);
}

void Site::develop()
{
    species = 4;
}

int Site::getSpecies()
{
    return species;
}

Site* Site::getNeighbor(int index)
{
    return neighbors[index];
}

void Site::growIntoNeighbor(int index)
{
    if (neighbors[index]->isDeveloped()==false)
    {
        neighbors[index]->grow(species);
    }
    
}


