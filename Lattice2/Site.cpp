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
void Site::grow(int new_species)
{
    species = new_species;
}
bool Site::isEmpty()
{
    return (species==0);
}
void Site::fillNeighborArray(int numNeighbors, vector<Site*> newNeighbors)
{
    neighbors.resize(numNeighbors);
    for(int i  = 0; i<numNeighbors;i++)
    {
        neighbors.push_back(newNeighbors[i]);
    }
}
