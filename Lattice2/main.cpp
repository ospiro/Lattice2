//
//  main.cpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#include <iostream>
#include "Lattice.hpp"

int main(int argc, const char * argv[]) {
  

    int numSteps = 10000;
    
    
    
    int setWidth = 100;
    int setRadius = 10;
    double prob[4] = {0.3,0.1,0.3,0.3};//first index not used
    double setBirthRate[4] = {0,4,3.2,3};
    double setDeathRate[4] = {0,1,1,1};
    double setGrassDeathIncrement = 0.5;
    double setParasiteBirthIncrement = 0.2;
    int devType = 1;
    int setAmountDevelopment = 2500;
    
    
    Lattice myLattice(setWidth,
            setRadius,
            prob,
            setBirthRate,
            setDeathRate,
            setGrassDeathIncrement,
            setParasiteBirthIncrement,
            devType,
            setAmountDevelopment);
    for( int i = 0; i<numSteps;i++)
    {
        myLattice.advanceTimeStep();
        if(i%10==0)
        {
            myLattice.printLattice();

        }
            
    }
    
    return 0;
}
