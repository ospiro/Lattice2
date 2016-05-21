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
    
    void fillNeighborArray(int numNeighbors, vector<Site*> newNeighbors);
};



#endif /* Site_hpp */
