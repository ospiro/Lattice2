//
//  Lattice.hpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#ifndef Lattice_hpp
#define Lattice_hpp

#include <iostream>
#include <vector>
#include "Site.hpp"
#include <random>
using namespace std;
class Lattice
{
private:
    int width;
    std::vector<std::vector<Site>> lat;
    int numNeighbors; //TODO: Does this need to ba a data member? //Number of neighbors of each site
    double grassDeathIncrement; //TODO: make sure needs to be double, same for below.
    double parasiteBirthIncrement;
    double deathRate;
    double birthRate;
    int radius; //Interaction radius
    int amountDevelopment;
public:
    Lattice(int setWidth,
            int setRadius,
            double prob[4],
            double setBirthRate,
            double setDeathRate,
            double setGrassDeathIncrement,
            double setParasiteBirthIncrement,
            int devType,
            int setAmountDevelopment);
    mt19937 mt_rand;
};

#endif /* Lattice_hpp */
