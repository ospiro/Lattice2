//
//  Site.hpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#ifndef Site_hpp
#define Site_hpp

#include <iostream>
#include <vector>
using namespace std;
class Site
{
private:
    int species;
    std::vector<Site*> neighbors;
public:
    Site();
    void die();
    void grow(int new_species);
    bool isEmpty();
    bool isDeveloped();
    void develop();
    int getSpecies();
    Site* getNeighbor(int index);
    double getDeathRate();
    void growIntoNeighbor(int index);
    
    void fillNeighborArray(unsigned long numNeighbors, vector<Site*> newNeighbors); //TODO: Is unsigned long necessary? loses precision when converting stepI.size() to int but probably not a problem.
};



#endif /* Site_hpp */
