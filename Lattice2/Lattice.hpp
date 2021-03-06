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
#include <stdexcept>
using namespace std;
class Lattice
{
private:
    int width;
    int numNeighbors; //TODO: Does this need to ba a data member? //Number of neighbors of each site
    double parasiteOnGrassDeathIncrement; //TODO: make sure needs to be double, same for below.
    double forbOnGrassDeathIncrement;
    double parasiteBirthIncrement;
    double deathRate[4];
    double birthRate[4];
    double radius; //Interaction radius
    int amountDevelopment;
    double dt;
public:
    Lattice(int setWidth,
            double setRadius,
            double prob[4],
            double setBirthRate[4],
            double setDeathRate[4],
            double setParasiteOnGrass,
            double setForbOnGrass,
            double setParasiteBirthIncrement,
            int devType,
            int setAmountDevelopment);
    void addDevelopment(int devType, int amountDevelopment);
    void printLattice();
    double wellMix();
    double getDeathRate(Site S);
    void checkEvent(int ii,int jj);
    void advanceTimeStep();
    vector<int> countPopulation();
    bool checkConnected();
    bool checkExtinction();
    std::vector<std::vector<Site>> lat; //TODO: return to private after debugging
    mt19937 mt_rand;
    std::vector<std::vector<int>> shortestPath(int i,int j);
    
    
    
    
    //===========TEST SUITE=========================
    void testNeighbors();
    void testCheckEvent();
    void testAdvanceTimeStep();
    void testCheckConnected();
    
    
    
    
    
    
    
    
};

#endif /* Lattice_hpp */
